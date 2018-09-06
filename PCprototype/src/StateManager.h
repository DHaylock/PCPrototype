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
        static StateManager * instance_ = nullptr;
        if(instance_ == nullptr)
        {
            instance_ = new StateManager();
            PCMessage("State Manager", "[Success]: Created State Manager");
        }
        
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
    
    ofParameter <int> currentMode { "Mode", static_cast<int>(Mode::Debug) };
    
private:
    vector <string> states;
};

#endif /* StateManager_h */
