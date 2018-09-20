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

#define COLOR_1 ofColor::fromHex(0x0000ff)
#define COLOR_2 ofColor::fromHex(0xff5707)
#define COLOR_3 ofColor::fromHex(0xec008c)

//--------------------------------------------------------------
enum class Effects
{
    Mouse,
    SpinningDots,
    SpinningLines,
    Fountain,
    Fireworks,
    BlockColor,
    FadeToWhite,
    RotatingCircles,
    Shader
};

//--------------------------------------------------------------
enum class Mode {
    Debug,
    KenKenPa,
    PhysicalToy
};

//--------------------------------------------------------------
enum class KenKenState {
    Attractor,
    Explainer,
    Countdown,
    Game,
    Reward
};

//--------------------------------------------------------------
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

struct ModeTriggerKeys {
    ModeTriggerKeys(){}
    ModeTriggerKeys(int allStopKey,
                int attractorModeKey,
                int explainerModeKey,
                int countdownModeKey,
                int gameModeKey,
                int winModeKey)
    {
        this->allStopKey = allStopKey;
        this->attractorModeKey = attractorModeKey;
        this->explainerModeKey = explainerModeKey;
        this->countdownModeKey = countdownModeKey;
        this->gameModeKey = gameModeKey;
        this->winModeKey = winModeKey;
    }
    
    int allStopKey;
    int attractorModeKey;
    int explainerModeKey;
    int countdownModeKey;
    int gameModeKey;
    int winModeKey;
};

struct PlayerTriggerKeys
{
    PlayerTriggerKeys() {}
    PlayerTriggerKeys(int player1StartKey,
                      int player1EndKey,
                      int player2StartKey,
                      int player2EndKey,
                      int dualPlayersStartKey,
                      int dualPlayersEndKey)
    {
        this->player1StartKey = player1StartKey;
        this->player1EndKey = player1EndKey;
        this->player2StartKey = player2StartKey;
        this->player2EndKey = player2EndKey;
        this->dualPlayersStartKey = dualPlayersStartKey;
        this->dualPlayersEndKey = dualPlayersEndKey;
    }
    
    int player1StartKey;
    int player1EndKey;
    int player2StartKey;
    int player2EndKey;
    int dualPlayersStartKey;
    int dualPlayersEndKey;
};

//--------------------------------------------------------------
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

//--------------------------------------------------------------
struct KenKenPaData {
    KenKenPaData() {}
    KenKenPaData(ModeTriggerKeys mK,
                 PlayerTriggerKeys pK,
                 string boostFile1,
                 string boostFile2,
                 string boostFile3,
                 string boostFile4,
                 vector<KenKenPa> versions)
    {
        this->mK = mK;
        this->pK = pK;
        this->boostFile1 = boostFile1;
        this->boostFile2 = boostFile2;
        this->boostFile3 = boostFile3;
        this->boostFile4 = boostFile4;
        this->versions = versions;
    }
    
    
    ModeTriggerKeys mK;
    PlayerTriggerKeys pK;
    
    int boost1StartKey;
    int boost2StartKey;
    int boost3StartKey;
    int boost4StartKey;
    string boostFile1;
    string boostFile2;
    string boostFile3;
    string boostFile4;
    
    vector<KenKenPa> versions;
};

#include "StateManager.h"
#include "Config.h"
#include "Stopwatch.h"
#include "Timer.h"
#include "ofVideoPlayer_ext.h"
#include "DebugEffects.h"
