#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(20);
    uarm.setup("/dev/tty.usbserial-A600CRMU", 9600);
    
    ofBackground(40, 40, 30);
    
    receiver.setup(PORT);
    
    i = 0;
    armXpos = 0;
    armYpos = 0;
    armZpos = ZUP;
    moveArm = false;
    
    myip.setup();
    
    vector<ofxMyIPAddress> list = myip.getList();
    
    stringstream s;
    for (vector<ofxMyIPAddress>::iterator o = list.begin(); o != list.end(); o++) {
        s << o->address << endl;
    }
    result = s.str();
    
}

//--------------------------------------------------------------
// x, y, z in cylindrical coordinates, handRot in degrees
void ofApp::setArmTo(int x, int y, int z, int handRot, int gripper) {
    // UArm expects 1 for an open gripper and 2 for a closed gripper
    gripper = (int)gripper + 1;
    unsigned char bytes[11] = {
        0xFF,
        0xAA,
        static_cast<unsigned char>((x >> 8) & 0xFF),
        static_cast<unsigned char>(x & 0xFF),
        static_cast<unsigned char>((y >> 8) & 0xFF),
        static_cast<unsigned char>(y & 0xFF),
        static_cast<unsigned char>((z >> 8) & 0xFF),
        static_cast<unsigned char>(z & 0xFF),
        static_cast<unsigned char>((handRot >> 8) & 0xFF),
        static_cast<unsigned char>(handRot & 0xFF),
        static_cast<unsigned char>(gripper)
    };
    uarm.writeBytes(&bytes[0], 11);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    moveArm = false;
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/mouse/position"){
            inputX = (int)(XRANGE*m.getArgAsFloat(1));
            inputY = (int)(YRANGE*m.getArgAsFloat(0));
            
            armXpos = inputX;
            armYpos = inputY;
            
            moveArm = true;
            
            if(m.getArgAsInt(2) == 1){
                armZpos = ZDOWN;
            } else {
                armZpos = ZUP;
            }

        }
        
        if(m.getAddress() == "/mouse/button"){
            if(m.getArgAsInt(0) == 1 && armZpos == ZUP){
                armZpos = ZDOWN;
                moveArm = true;
            } else if(m.getArgAsInt(0) == 0 && armZpos == ZDOWN) {
                armZpos = ZUP;
                moveArm = true;
            }
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(moveArm){
        setArmTo(armXpos,armYpos,armZpos,0,0);
    }
    
    ofDrawBitmapString("Om.", 10, 20);
    ofDrawBitmapString(result, 10, 55);
    
}

//--------------------------------------------------------------
void ofApp::exit() {
    uarm.flush(true,true);
}
