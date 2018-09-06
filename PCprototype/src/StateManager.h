//--------------------------------------------------------------
//  StateManager.h
//  PCprototype
//  Created by David Haylock on 30/08/2018.
//! PCprototype
/** StateManager Class */
//-------------------------------------------------------------

#ifndef StateManager_h
#define StateManager_h

#include "pcmain.h"

class StateManager {
public:
    /**
     Instance Creator
     */
    //-------------------------------------------------------------
    static StateManager &instance()
    {
        static StateManager* instance_= new StateManager();
        return *instance_;
    }
    
    
    /**
     Returns the Current Mode

     @return mode
     */
    //-------------------------------------------------------------
    int getCurrentMode()
    {
        return currentMode;
    }
    
    ofParameterGroup parameters;
    ofParameter <int> currentMode { "Mode", static_cast<int>(Mode::Debug) };
    
private:
    vector <string> states;
};

#endif /* StateManager_h */
