//
//  StateManager.h
//  PCprototype
//
//  Created by David Haylock on 16/08/2018.
//

#ifndef StateManager_h
#define StateManager_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxJSON.h"

class StateManager {
    public:
    
    /**
     Create an Instance of the StateManager

     @return instance
     */
    //--------------------------------------------------------------
    static StateManager & instance() {
        static StateManager* instance_ = new StateManager();
        return *instance_;
    }
    
    
    
};


#endif /* StateManager_h */
