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
    int getKenKenState()
    {
        return currentKenKenState;
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
    
    /**
     Returns the KenkenPa Mode
     
     @return mode
     */
    //-------------------------------------------------------------
    int getKenKenPaMode()
    {
        return currentMode;
    }
    
    ofParameter <int> currentMode { "Mode", static_cast<int>(Mode::Debug) };
    ofParameter <int> currentKenKenState { "Ken Ken State", static_cast<int>(KenKenState::Attractor) };
    ofParameter <int> currentKenKenMode { "Ken Ken Mode", static_cast<int>(KenKenMode::OnePlayer) };
    ofParameter <int> currentEffect { "Debug Effect", static_cast<int>(Effects::Mouse) };
    
private:
    vector <string> states;
};

#endif /* StateManager_h */
