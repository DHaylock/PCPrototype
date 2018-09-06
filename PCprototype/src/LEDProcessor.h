//
//  LEDProcessor.h
//  PCprototype
//
//  Created by David Haylock on 14/08/2018.
//

#ifndef LEDProcessor_h
#define LEDProcessor_h

#include <stdio.h>
#include "ofxAutoReloadedShader.h"
#include "pcmain.h"

class LEDProcessor {
    public:
    
        /**
         Initialise the Processor
         */
        //--------------------------------------------------------------
        void init();
    
        /**
         Start Capturing the Screen
         */
        //--------------------------------------------------------------
        void startCapture();
    
        /**
         End Capturing the Screen
         */
        //--------------------------------------------------------------
        void endCapture();
    
        /**
         Draw the Result
         */
        //--------------------------------------------------------------
        void render();
    
        ofParameterGroup parameters;
        ofParameter<bool> active;
        ofParameter<int> pixelSize;
        ofParameter<float> vignetteAmount;
        ofParameter<ofFloatColor> tintColor;
    
    private:
    
        ofFbo shaderBuffer;
        ofxAutoReloadedShader shader;
};


#endif /* LEDProcessor_h */
