//
//  vision.cpp
//  areaBreak
//
//  Created by Felipe L. Navarro on 14/08/17.
//
//

#include "vision.h"

//--------------------------------------------------------------
void vision::setup(){
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(320, 240);
    
    colorImg.allocate(320, 240);
    grayImg.allocate(320, 240);
    grayBg.allocate(320, 240);
    grayDiff.allocate(320, 240);
    
    threshold = 80;
    
    learnBackground();
}

//--------------------------------------------------------------
void vision::update(){
    bool bNewFrame = false;
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
    if(bNewFrame){
        colorImg.setFromPixels(vidGrabber.getPixels());
        
        grayImg = colorImg;
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImg);
        grayDiff.threshold(threshold);
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, false);
    }
}

//--------------------------------------------------------------
void vision::draw(){
    if(drawVisionGUI){
        // draw the incoming, the grayscale, the bg and the thresholded difference
        ofSetHexColor(0xffffff);
        colorImg.draw(20,20);
        grayImg.draw(360,20);
        grayBg.draw(20,280);
        grayDiff.draw(360,280);
        
        // then draw the contours:
        
        ofFill();
        ofSetHexColor(0x333333);
        ofDrawRectangle(360,540,320,240);
        ofSetHexColor(0xffffff);
        
        // we could draw the whole contour finder
        //contourFinder.draw(360,540);
        
        // or, instead we can draw each blob individually from the blobs vector,
        // this is how to get access to them:
        for (int i = 0; i < contourFinder.nBlobs; i++){
            contourFinder.blobs[i].draw(360,540);
            
            // draw over the centroid if the blob is a hole
            ofSetColor(255);
            if(contourFinder.blobs[i].hole){
                ofDrawBitmapString("hole",
                                   contourFinder.blobs[i].boundingRect.getCenter().x + 360,
                                   contourFinder.blobs[i].boundingRect.getCenter().y + 540);
            }
        }
        
        // finally, a report:
        ofSetHexColor(0xffffff);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
        << "press ' ' to capture bg" << endl
        << "threshold " << threshold << " (press: +/-)" << endl
        << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
        ofDrawBitmapString(reportStr.str(), 20, 600);
    }
}

//--------------------------------------------------------------
void vision::learnBackground(){
    grayBg = grayImg;
}

//--------------------------------------------------------------
void vision::changeThreshold(bool sum){
    if(sum){
        threshold ++;
        if (threshold > 255) threshold = 255;
    } else {
        threshold --;
        if (threshold < 0) threshold = 0;
    }
}

//--------------------------------------------------------------
void vision::showGUI(bool show){
    drawVisionGUI = !drawVisionGUI;
}