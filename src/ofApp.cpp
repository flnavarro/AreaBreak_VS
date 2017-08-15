#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Window
    backgroundColor = ofColor(0, 0, 153, 255);
    ofBackground(backgroundColor);
    ofSetWindowTitle("Touch Wall v0.1");
    WIDTH=1920;
    HEIGHT=1080;
    fullscreen = true;
    ofSetFullscreen(fullscreen);

    interactiveGraphics.setup(WIDTH, HEIGHT, backgroundColor);
    computerVision.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    interactiveGraphics.update();
    computerVision.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    interactiveGraphics.draw();
    computerVision.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f' || key == 'F'){
        fullscreen = !fullscreen;
        ofSetFullscreen(fullscreen);
    }
    
    if(key == 'v' || key == 'V'){
        computerVision.showGUI(!computerVision.drawVisionGUI);
    }
    
    if(key == ' '){
        computerVision.learnBackground();
    }
    
    if(key == '+'){
        computerVision.changeThreshold(true);
    }
    
    if(key == '-'){
        computerVision.changeThreshold(false);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // interactiveGraphics.initCircles(x, y);
    interactiveGraphics.initWords(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}