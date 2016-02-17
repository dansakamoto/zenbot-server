# Zenbot (server app)
Zenbot is a zen garden that you can interact with remotely via a robotic arm holding a small rake.

This OpenFrameworks app waits for commands received from [the client-side app](https://github.com/dansakamoto/zenbot-client) and then passes them along to the a uArm connected via USB.

This app includes [the ofxOsc addon by Hideyuki Saito](https://github.com/hideyukisaito/ofxOsc), [the ofxMyIP addon by Satoshi HORII](https://github.com/satcy/ofxMyIP), and [code for interfacing with the uArm written by Aman Tiwari](https://gist.github.com/aman-tiwari/95308a11416e2fccb971).