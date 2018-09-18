//
//  VisualManager.cpp
//  PCprototype
//
//  Created by David Haylock on 15/08/2018.
//

#include "VisualManager.h"

//--------------------------------------------------------------
void VisualManager::init()
{
    ofAddListener(ofEvents().keyPressed, this, &VisualManager::keyPress);
    DebugEffects::instance().init();
    kenkenpa.init();
    
    parameters.setName("Visual Manager");
    parameters.add(kenkenpa.versionNo);
    parameters.add(kenkenpa.bLoad);
}

//--------------------------------------------------------------
void VisualManager::update()
{
    
}

//--------------------------------------------------------------
void VisualManager::draw()
{
    switch(StateManager::instance().getCurrentMode())
    {
        case static_cast<int>(Mode::Debug):
        {
            DebugEffects::instance().render();
        }
            break;
        case static_cast<int>(Mode::KenKenPa):
        {
            kenkenpa.render();
        }
            break;
        case static_cast<int>(Mode::PhysicalToy):
        {
            
        }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void VisualManager::keyPress(ofKeyEventArgs &key)
{
    
}

