//
//  pcmain.h
//  PCprototype
//
//  Created by David Haylock on 06/09/2018.
//

#pragma once

#include "ofMain.h"
#include "ofxEasing.h"
#include "ofxImGui.h"
#include "Tween.h"

enum class Mode {
    Debug,
    KenKenPa,
    PhysicalToy
};

//-----------------------------------------------------
/**
 Logging Message System
 
 @param s_Class Class / Manager Message Sent from
 @param s_Message message
 */
//-----------------------------------------------------
template<typename T>
void PCMessage(T s_Class,T s_Message) {
    string msg = string(s_Class) + " | " + string(s_Message);
    ofSendMessage(msg);
}


#include "StateManager.h"

