#pragma once

#include "ofMain.h"
#include "LEDProcessor.h"
#include "VisualManager.h"
#include "pcmain.h"

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
    
        void drawGui();
    
        ofxImGui::Gui gui;
        bool bGuiVisible;
        bool bMouseOverGui;
    
        ofParameterGroup parameters;
        bool bDrawGui = false;

        // Debug Stuff
        void gotMessage(ofMessage msg);
        int logSize;
        deque <string> logs;
};

