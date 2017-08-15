//
//  graphics.cpp
//  areaBreak
//
//  Created by Felipe L. Navarro on 14/08/17.
//
//

#include "graphics.h"


//--------------------------------------------------------------
void graphics::setup(int windowW, int windowH, ofColor bckgrdColor){
    // Window
    WIDTH = windowW;
    HEIGHT = windowH;
    backgroundColor = bckgrdColor;
    
    state = "lines";
    // state = "words";
    
    // Lines
    timeWaiting = 1;
    initLines();
    maxWidthWordBox = 500;
    heightWordBox = 150;
    wordBoxCenterPos = ofVec2f(300, HEIGHT/2);
    
    // Circles
    circle.load("imgs/ab_circle.png");
    circleMaxScale = 0.5;
    maxOpenings = 3;
    maxRotations = 2;
    maxDegreeRotation = 120;
    maxBlinking = 4;
    blinkingTime = 0.1;
    initCircles(500, 500);
    
    // Words
    wordFont.load("fonts/UniversLTStd-LightCn.otf", 95, true);
    wordMaxFrames = 100;
    loadWords();
}

//--------------------------------------------------------------
void graphics::loadWords(){
    ofDirectory dW;
    ofDirectory dI;
    dW.listDir("wordImgs");
    for(int i=0; i<dW.size(); i++){
        dI.listDir("wordImgs/word_" + ofToString(i+1));
        vector <ofImage> wI;
        for(int j=0; j<dI.size(); j++){
            wI.push_back(ofImage());
            wI[j].load(dI.getPath(j));
        }
        wordImgs.push_back(wI);
    }
}

//--------------------------------------------------------------
void graphics::initWords(int posX, int posY){
    state = "words";
    wordPos.x = posX;
    wordPos.y = posY;
    wordIdx = (int)ofRandom(wordImgs.size());
    wordLetterSpacing = 0;
    wordResizeFactor = 0.5;
    wordAlpha = 255;
    wordFrame = 0;
    wordFbo.allocate(1920, 1080);
    // wordFbo.allocate(1920, wordImgs[wordIdx][0].getHeight());
    // glowFx.setup(&wordFbo);
    // glowFx.setFx(OFXPOSTGLITCH_GLOW, true);
    if(posX <= WIDTH/2){
        wordRotated = false;
    } else {
        wordRotated = true;
    }
}

//--------------------------------------------------------------
void graphics::update(){
    if(state == "lines"){
        updateLines();
    }
    else if(state == "circles"){
        updateCircles();
    }
    else if(state == "words"){
        updateWords();
    }
}

//--------------------------------------------------------------
void graphics::updateWords(){
    if(wordFrame<wordMaxFrames){
        if(wordRotated){
            wordLetterSpacing = ofMap(wordFrame, 0, wordMaxFrames, 0, -100);
        } else {
            wordLetterSpacing = ofMap(wordFrame, 0, wordMaxFrames, 0, 100);
        }
        wordAlpha = ofMap(wordFrame, 0, wordMaxFrames, 255, 0);
    } else {
       state = "lines";
    }
    wordFrame++;
    
//    wordFbo.begin();
//    ofClear(0, 0, 0, 255);
//    ofPushStyle();
//    ofSetColor(255, 255, 255, wordAlpha);
//    for(int i=0; i<wordImgs[wordIdx].size(); i++){
//        if(i==0){
//            wordImgs[wordIdx][i].draw(wordPos.x, 0,
//                                      wordImgs[wordIdx][i].getWidth()*wordResizeFactor,
//                                      wordImgs[wordIdx][i].getHeight()*wordResizeFactor);
//        }else{
//            wordImgs[wordIdx][i].draw(wordPos.x+wordLetterSpacing*i, 0,
//                                      wordImgs[wordIdx][i].getWidth()*wordResizeFactor,
//                                      wordImgs[wordIdx][i].getHeight()*wordResizeFactor);
//        }
//    }
//    ofPopStyle();
//    wordFbo.end();

}

//--------------------------------------------------------------
void graphics::draw(){
    if(state == "lines"){
        drawLines();
    }
    
    else if(state == "circles"){
        drawCircles();
    }
    
    else if(state == "words"){
        drawWords();
    }
}

//--------------------------------------------------------------
void graphics::drawWords(){
//    ofPushStyle();
//    ofSetColor(255, 255, 255, 255);
//    wordFbo.draw(0,wordPos.y);
//    glowFx.generateFx();
//    ofPopStyle();
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(wordPos.x, wordPos.y);
    ofScale(wordResizeFactor, wordResizeFactor);
    if(wordRotated){
        ofRotate(180);
    }
    ofPushMatrix();
    ofTranslate(-wordPos.x, -wordPos.y);
    for(int i=0; i<wordImgs[wordIdx].size(); i++){
        ofSetColor(255, 255, 255, wordAlpha);
        if(i==0){
            wordImgs[wordIdx][i].draw(wordPos.x, wordPos.y);
        } else {
            if(wordRotated){
                wordImgs[wordIdx][i].draw(wordPos.x - wordLetterSpacing*i, wordPos.y);
            } else {
                wordImgs[wordIdx][i].draw(wordPos.x + wordLetterSpacing*i, wordPos.y);
            }
        }
    }
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void graphics::initLines(){
    lineBuilding = true;
    lineWaiting = false;
    lineWordBox = false;
    lineWordBox_open = false;
    lineOpening = false;
    lineClosing = false;
    restart = false;
    nLines = ofRandom(10,30);
    separation = (float)HEIGHT/(float)nLines;
    posLength = 0;
    negLength = WIDTH;
    separLineWord = separation;
    widthWordBox = 0;
    letterSpacing = 0.0;
}

//--------------------------------------------------------------
void graphics::initCircles(int posX, int posY){
    state = "circles";
    circlePos = ofVec2f(posX-circle.getWidth()/2, posY-circle.getHeight()/2);
    circleOpening = true;
    circleRotating = false;
    circleBlinking = false;
    circleClosing = false;
    circleScale = 0.0;
    nOpening = 0;
    nRotations = 0;
    circleRotation = 0;
    positiveRotation = true;
    nBlinking = 0;
    blinkShow = false;
}

//--------------------------------------------------------------
void graphics::updateLines(){
    if(lineBuilding){
        if(posLength+1 < WIDTH && negLength-1 > 0){
            posLength += 10;
            negLength -= 10;
        } else {
            lineBuilding = false;
            elapsedWaiting = ofGetElapsedTimef();
            lineWaiting = true;
        }
    }
    
    if(lineWaiting){
        if(ofGetElapsedTimef()-elapsedWaiting>timeWaiting){
            lineWaiting = false;
            lineWordBox = true;
            lineWordBox_open = true;
            lineWordBox_wait_1 = false;
            lineWordBox_close = false;
        }
    }
    
    if(lineWordBox){
        if(lineWordBox_open){
            if(widthWordBox>maxWidthWordBox){
                lineWordBox_open = false;
                lineWordBox_wait_1 = true;
                elapsedWaiting = ofGetElapsedTimef();
            }
            widthWordBox+=10;
            //letterSpacing+=0.01;
        }
        if(lineWordBox_wait_1){
            if(ofGetElapsedTimef()-elapsedWaiting>timeWaiting){
                lineWordBox_wait_1 = false;
                lineWordBox_close = true;
            }
        }
        if(lineWordBox_close){
            if(widthWordBox<0){
                lineWordBox_close = false;
                lineWordBox = false;
                lineOpening = true;
            }
            widthWordBox-=10;
        }
    }
    
    if(lineOpening){
        int sepIncrease = 1;
        if(separation>HEIGHT/2 && separation<HEIGHT){
            sepIncrease = 10;
        } else if(separation>HEIGHT){
            lineOpening = false;
            lineClosing = true;
        }
        separation += sepIncrease;
    }
    
    if(lineClosing){
        if(separation < -200){
            lineClosing = false;
            restart = true;
        }
        separation--;
    }
    
    if(restart){
        initLines();
    }
    
    ofLog() << "lineOpening " << lineOpening;
    ofLog() << "separation " << separation;
}

//--------------------------------------------------------------
void graphics::updateCircles(){
    if(circleOpening){
        if(nOpening < maxOpenings){
            if(circleScale>circleMaxScale){
                nOpening++;
                if(nOpening!=maxOpenings){
                    circleScale = 0.0;
                }
            }
            circleScale += 0.01;
        } else {
            circleOpening = false;
            circleRotating = true;
        }
    }
    
    if(circleRotating){
        if(nRotations<maxRotations){
            if(positiveRotation){
                if(circleRotation>=maxDegreeRotation){
                    nRotations++;
                    positiveRotation = false;
                }
                circleRotation += 1.25;
            }else{
                if(circleRotation<=0){
                    nRotations++;
                    positiveRotation = true;
                }
                circleRotation -= 1.25;
            }
        } else {
            circleRotating = false;
            circleBlinking = true;
            elapsedBlinking = ofGetElapsedTimef();
        }
    }
    
    if(circleBlinking){
        if(nBlinking<maxBlinking){
            if(ofGetElapsedTimef()-elapsedBlinking>blinkingTime){
                elapsedBlinking = ofGetElapsedTimef();
                blinkShow = !blinkShow;
                nBlinking++;
            }
        } else {
            circleBlinking = false;
            circleClosing = true;
        }
    }
    
    if(circleClosing){
        if(circleScale<0){
            circleClosing=false;
            state = "lines";
            initLines();
        }
        circleScale -= 0.01;
    }
}

//--------------------------------------------------------------
void graphics::drawLines(){
    ofPushStyle();
    ofSetColor(255, 255, 255, 255);
    ofSetLineWidth(5);
    float posY = separation/2;
    for(int i=0; i<nLines; i++){
        if(i%2 == 0){
            ofDrawLine(0, posY, posLength, posY);
        }else{
            ofDrawLine(WIDTH, posY, negLength, posY);
        }
        posY += separation;
    }
    ofPopStyle();
    
    if(lineWordBox){

        ofPushMatrix();
        ofPushStyle();
        ofSetColor(backgroundColor);
        ofDrawRectangle(wordBoxCenterPos.x-heightWordBox/2, 0, heightWordBox, HEIGHT);
        ofSetColor(255, 255, 255, 255);
        wordFont.setLetterSpacing(letterSpacing);
        ofTranslate(wordBoxCenterPos.x-wordFont.stringWidth("PREMIUM")/2 + wordFont.stringWidth("PREMIUM")/2,
                    wordBoxCenterPos.y-wordFont.stringHeight("PREMIUM")/2 + wordFont.stringHeight("PREMIUM")/2);
        ofRotate(90);
        ofTranslate(-(wordBoxCenterPos.x-wordFont.stringWidth("PREMIUM")/2) - wordFont.stringWidth("PREMIUM")/2,
                    -(wordBoxCenterPos.y-wordFont.stringHeight("PREMIUM")/2) - wordFont.stringHeight("PREMIUM")/2);
        wordFont.drawString("PREMIUM", wordBoxCenterPos.x-wordFont.stringWidth("PREMIUM")/2-15,
                            wordBoxCenterPos.y+100-wordFont.stringHeight("PREMIUM")/2);
        ofPopStyle();
        ofPopMatrix();
        
        ofPushMatrix();
        ofPushStyle();
        ofSetColor(backgroundColor);
        ofDrawRectangle(wordBoxCenterPos.x-heightWordBox/2, 0, heightWordBox, HEIGHT/2-widthWordBox/2);
        ofDrawRectangle(wordBoxCenterPos.x-heightWordBox/2, HEIGHT/2+widthWordBox/2, heightWordBox, HEIGHT);
        ofPopStyle();
        ofPopMatrix();
        
        ofPushMatrix();
        ofPushStyle();
        ofSetColor(255, 255, 255, 255);
        ofSetLineWidth(5);
        float posY = separation/2;
        for(int i=0; i<nLines; i++){
            if(i < (int)(nLines/2)){
                ofDrawLine(wordBoxCenterPos.x-heightWordBox/2, posY-widthWordBox/2, wordBoxCenterPos.x+heightWordBox/2, posY-widthWordBox/2);
            } else {
                ofDrawLine(wordBoxCenterPos.x-heightWordBox/2, posY+widthWordBox/2, wordBoxCenterPos.x+heightWordBox/2, posY+widthWordBox/2);
            }
            posY += separation;
        }
        ofPopStyle();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void graphics::drawCircles(){
    if(circleOpening){
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(circlePos.x + circle.getWidth()/2, circlePos.y + circle.getHeight()/2);
        ofScale(circleScale, circleScale);
        ofPushMatrix();
        ofTranslate(-circlePos.x - circle.getWidth()/2, -circlePos.y - circle.getHeight()/2);
        ofSetColor(255, 255, 255, 255);
        circle.draw(circlePos.x, circlePos.y);
        ofPopMatrix();
        ofPopMatrix();
        ofPopStyle();
    }
    
    if(circleRotating){
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(circlePos.x + circle.getWidth()/2, circlePos.y + circle.getHeight()/2);
        ofScale(circleScale, circleScale);
        ofRotate(circleRotation);
        ofPushMatrix();
        ofTranslate(-circlePos.x - circle.getWidth()/2, -circlePos.y - circle.getHeight()/2);
        ofSetColor(255, 255, 255, 255);
        circle.draw(circlePos.x, circlePos.y);
        ofPopMatrix();
        ofPopMatrix();
        ofPopStyle();
    }
    
    if(circleBlinking){
        if(blinkShow){
            ofPushStyle();
            ofPushMatrix();
            ofTranslate(circlePos.x + circle.getWidth()/2, circlePos.y + circle.getHeight()/2);
            ofScale(circleScale, circleScale);
            ofPushMatrix();
            ofTranslate(-circlePos.x - circle.getWidth()/2, -circlePos.y - circle.getHeight()/2);
            ofSetColor(255, 255, 255, 255);
            circle.draw(circlePos.x, circlePos.y);
            ofPopMatrix();
            ofPopMatrix();
            ofPopStyle();
        }
    }
    
    if(circleClosing){
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(circlePos.x + circle.getWidth()/2, circlePos.y + circle.getHeight()/2);
        ofScale(circleScale, circleScale);
        ofPushMatrix();
        ofTranslate(-circlePos.x - circle.getWidth()/2, -circlePos.y - circle.getHeight()/2);
        ofSetColor(255, 255, 255, 255);
        circle.draw(circlePos.x, circlePos.y);
        ofPopMatrix();
        ofPopMatrix();
        ofPopStyle();
    }
}