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
#include "ofxCenteredTrueTypeFont.h"

enum class Effects
{
    Mouse,
    SpinningDots,
    SpinningLines,
    Noise,
    Waves,
    BlockColor,
    FadeToWhite,
    RotatingCircles,
    Gradient
};

enum class Mode {
    Debug,
    KenKenPa,
    PhysicalToy
};

enum class KenKenState {
    Attractor,
    Kiosk,
    Ready,
    Game,
    Reward
};

enum class KenKenMode {
    OnePlayer,
    TwoPlayers
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

struct KenKenPa {
    KenKenPa() {}
    KenKenPa(int id,
                  string name,
                  int waitOutTimer,
                  int attractorTimer,
                  string attractorFile,
                  string kioskFile,
                  string rewardFile)
    {
        this->id = id;
        this->name = name;
        this->waitOutTimer = waitOutTimer;
        this->attractorTimer = attractorTimer;
        this->attractorFile = attractorFile;
        this->kioskFile = kioskFile;
        this->rewardFile = rewardFile;
    }
    int id;
    string name;
    int waitOutTimer;
    int attractorTimer;
    string attractorFile;
    string kioskFile;
    string rewardFile;
};

struct KenKenPaData {
    KenKenPaData() {}
    KenKenPaData(int player1StartKey,int player1EndKey,int player2StartKey,int player2EndKey,int dualPlayersStartKey,int dualPlayersEndKey,vector<KenKenPa> versions)
    {
        this->player1StartKey = player1StartKey;
        this->player1EndKey = player1EndKey;
        this->player2StartKey = player2StartKey;
        this->player2EndKey = player2EndKey;
        this->dualPlayersStartKey = dualPlayersStartKey;
        this->dualPlayersEndKey = dualPlayersEndKey;
        this->versions = versions;
    }
    int player1StartKey;
    int player1EndKey;
    int player2StartKey;
    int player2EndKey;
    int dualPlayersStartKey;
    int dualPlayersEndKey;
    
    vector<KenKenPa> versions;
};

//struct PhysicalToyCombo
//{
//    PhysicalToyCombo() {}
//    PhysicalToyCombo()
//    {
//
//    }
//
//    vector<int> btns;
//}

//struct PhysicalToyData
//{
//    PhysicalToyData() {}
//    PhysicalToyData(int btn1Key,int btn2key,int btn3key,int btn4key)
//    {
//        this->btn1key = btn1key;
//        this->btn2key = btn2key;
//        this->btn3key = btn3key;
//        this->btn4key = btn4key;
//    }
//    
//    int btn1Key;
//    int btn2key;
//    int btn3key;
//    int btn4key;
//};

#include "StateManager.h"
#include "Config.h"
#include "Stopwatch.h"
#include "Timer.h"
#include "ofVideoPlayer_ext.h"
#include "DebugEffects.h"
