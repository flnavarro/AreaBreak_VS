//
//  graphics.hpp
//  areaBreak
//
//  Created by Felipe L. Navarro on 14/08/17.
//
//

#include "ofMain.h"
// #include "ofxPostGlitch.h"

class graphics {
    public:
        void setup(int windowW, int windowH, ofColor bckgrdColor);
        void update();
        void draw();
    
        void loadWords();
        void initWords(int posX, int posY);
        void updateWords();
        void drawWords();
    
        // Window
        int WIDTH;
        int HEIGHT;
        ofColor backgroundColor;
    
        // System
        string state;
        ofTrueTypeFont wordFont;
    
        // Words
        ofVec2f wordPos;
        vector<vector <ofImage>> wordImgs;
        int wordIdx;
        int wordLetterSpacing;
        float wordResizeFactor;
        int wordAlpha;
        int wordFrame;
        int wordMaxFrames;
        // ofxPostGlitch glowFx;
        ofFbo wordFbo;
        bool wordRotated;
    
    
    // --- FIRST V.---
    void initLines();
    void initCircles(int posX, int posY);
    void updateLines();
    void updateCircles();
    void drawLines();
    void drawCircles();
    
        // Lines
        int nLines;
        float separation;
        int posLength;
        int negLength;
        bool lineBuilding;
        bool lineWaiting;
        bool lineWordBox;
        bool lineWordBox_open;
        bool lineWordBox_wait_1;
        bool lineWordBox_close;
        bool lineOpening;
        bool lineClosing;
        bool restart;
        float timeWaiting;
        float elapsedWaiting;
        float separLineWord;
        float maxWidthWordBox;
        float heightWordBox;
        ofVec2f wordBoxCenterPos;
        float widthWordBox;
        float letterSpacing;
    
        // Circles
        ofImage circle;
        ofVec2f circlePos;
        float circleMaxScale;
        float circleScale;
        int maxOpenings;
        int nOpening;
        bool circleOpening;
        bool circleRotating;
        bool circleBlinking;
        bool circleClosing;
        int maxRotations;
        int nRotations;
        float circleRotation;
        bool positiveRotation;
        float elapsedBlinking;
        float blinkingTime;
        bool blinkShow;
        int maxBlinking;
        int nBlinking;
        float maxDegreeRotation;
};