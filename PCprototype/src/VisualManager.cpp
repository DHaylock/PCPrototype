//
//  VisualManager.cpp
//  PCprototype
//
//  Created by David Haylock on 15/08/2018.
//

#include "VisualManager.h"


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
//    if(key.key == OF_KEY_TAB || key.key == OF_KEY_RETURN || key.key == OF_KEY_LEFT_SHIFT || key.key == OF_KEY_RIGHT_SHIFT) {
//        
//        if(key.key == OF_KEY_RETURN) {
//            mode = !mode;
//        }
//        return;
//    }
//    else {
//        if(keymap.count((char)key.key) > 0) {
//            if (mode) {
//                currentVideo = keymap.at((char)key.key);
//                if (videos.size() > currentVideo) {
//                    videos[currentVideo].setPosition(0.0);
//                    videos[currentVideo].play();
//                }
//            }
//            else {
//                currentImage = keymap.at((char)key.key);
//            }
////            cout << key.key << " " << (char)key.key << endl;
//        }
//        else {
//            cout << "Invalid Action" << endl;
//            return;
//        }
//    }
}

