#pragma once

#include "ofMain.h"
#include "LEDProcessor.h"
#include "VisualManager.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
    
        LEDProcessor ledProcessor;
        VisualManager visualManager;
    
        void setupGUI();
        ofxPanel gui;
        ofParameterGroup parameters;
        ofxButton openRoot;
        bool showGui = false;
    
        void openRootFolder();
};
