//
//  VisualManager.h
//  PCprototype
//
//  Created by David Haylock on 15/08/2018.
//

#ifndef VisualManager_h
#define VisualManager_h

#include <stdio.h>
#include "ofxGui.h"
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

enum class DISPLAY_MODE {
    VIDEOS,
    PICTURES,
    TEXT,
    INTERACTIVE,
    DATA
};

class VisualManager {
  
    public:
    
        /**
         Setup the Manager
         */
        //--------------------------------------------------------------
        void setup();
    
        /**
         Load the Files
         */
        //--------------------------------------------------------------
        void loadVideos();
        void loadImages();
    
        /**
         Update
         This runs any animations or movement
         */
        //--------------------------------------------------------------
        void update();
    
        /**
         Does what it says on the tin
         */
        //--------------------------------------------------------------
        void draw();
    
        /**
         Reloads the display folder
         */
        //--------------------------------------------------------------
        void reloadContent();
    
        /**
         Key Press

         @param key key code
         */
        //--------------------------------------------------------------
        void keyPress(ofKeyEventArgs &key);
    
        ofParameterGroup parameters;
        ofParameter<int> currentVideo;
        ofParameter<int> currentImage;
        ofParameter<bool> mode;
    
        vector<ofVideoPlayer> videos;
    
        ofxThreadedImageLoader loader;
        vector<ofImage> images;
        map<char,int> keymap;
};

#endif /* VisualManager_h */
