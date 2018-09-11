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
            ofPushStyle();
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            float rotationAmount = ofGetElapsedTimeMillis()/10;
            float circ1Size = 40 + 40 * abs(sin(ofGetElapsedTimef()));
            float circ2Size = 40 + 40 * abs(cos(ofGetElapsedTimef()));
            ofSetColor(255, 0, 0);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2-circ1Size, circ1Size);
            ofPopMatrix();
            ofPopMatrix();
            ofSetColor(0, 0, 255);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(-rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2+circ2Size, circ2Size);
            ofPopMatrix();
            ofPopMatrix();
            ofDisableBlendMode();
            ofPopStyle();
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

