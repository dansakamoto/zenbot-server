#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxMyIP.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

#define ZUP 40
#define ZDOWN -6
#define DOWNTIME 15
#define XRANGE 30
#define YRANGE 80

class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    ofSerial uarm;
    void setArmTo(int x, int y, int z, int handRot, int gripper);
    
    ofxOscReceiver receiver;
    
    int i;
    int armXpos;
    int armYpos;
    int armZpos;
    
    int inputX;
    int inputY;
    
    bool moveArm;
    
    ofxMyIP myip;
    string result;
    
};
