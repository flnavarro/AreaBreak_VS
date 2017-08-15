//
//  vision.hpp
//  areaBreak
//
//  Created by Felipe L. Navarro on 14/08/17.
//
//

#include "ofMain.h"
#include "ofxOpenCv.h"

typedef enum{
    BG_ABS,
    BG_GREATER,
    BG_LESS
}captureMode;


class vision {
public:
    void setup();
    void update();
    void draw();
    
    void learnBackground();
    void changeThreshold(bool sum);
    void showGUI(bool show);
    
    void getQuadSubImage(unsigned char * inputData, unsigned char * outputData,
                         int inW, int inH, int outW, int outH,
                         int x1, int y1, int x2, int y2,
                         int x3, int y3, int x4, int y4, int bpp);
    
    void cameraMode(int mode);
    
    ofVideoGrabber vidGrabber;
    
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImg;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    
    ofxCvContourFinder contourFinder;
    
    int threshold;
    
    bool drawVisionGUI;

};