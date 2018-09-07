//
//  VisualManager.h
//  PCprototype
//
//  Created by David Haylock on 15/08/2018.
//

#ifndef VisualManager_h
#define VisualManager_h

#include <stdio.h>
#include "ofMain.h"
#include "KenKenPaManager.h"

class VisualManager {
  
    public:
    
        /**
         Setup the Manager
         */
        //--------------------------------------------------------------
        void init();
    
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
         Key Press

         @param key key code
         */
        //--------------------------------------------------------------
        void keyPress(ofKeyEventArgs &key);
    
        KenKenPaManager kenkenpa;
    
        ofParameterGroup parameters;
};

#endif /* VisualManager_h */
