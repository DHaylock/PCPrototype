//--------------------------------------------------------------
//  KenKenPaManager
//  PCprototype
//  Created by David Haylock on 30/08/2018.
//! PCprototype
/** KenKenPaManager Class */
//-------------------------------------------------------------

#ifndef KenKenPaManager_h
#define KenKenPaManager_h

#include <stdio.h>
#include "pcmain.h"

class KenKenPaManager {
public:
    
    /**
     Initialize Manager
     */
    //--------------------------------------------------------------
    void init();

    /**
     Load a new Version
     @params version
     */
    //--------------------------------------------------------------
    void loadVersion(bool &val);
    
    /**
     Render the Videos
     */
    //--------------------------------------------------------------
    void render();
    
    /**
     Render the ready process
     */
    //--------------------------------------------------------------
    void renderReadyState();
    
    /**
     Render the Game  State
     */
    //--------------------------------------------------------------
    void renderGameState();
    
    /**
     Render the End Game State
     */
    //--------------------------------------------------------------
    void renderRewardGameState();
    
    /**
     All Stop
     */
    //--------------------------------------------------------------
    void allStop();
    
    /**
     Set To Attractor Mode
     */
    //--------------------------------------------------------------
    void setAttractorMode();
    
    /**
     Set To Explainer Mode
     */
    //--------------------------------------------------------------
    void setExplainerMode();
    
    /**
     Set To Countdown Mode
     */
    //--------------------------------------------------------------
    void setCountdownMode();
    
    /**
     Set To Game Mode
     */
    //--------------------------------------------------------------
    void setGameMode();
    
    /**
     Set To Game Mode
     */
    //--------------------------------------------------------------
    void setRewardMode();
    
    /**
     Key Pressed Event

     @param key what key
     */
    //--------------------------------------------------------------
    void keyPressed(ofKeyEventArgs &key);
    
    Timer waitOutTimer;
    Timer attractorTimer;
    
    // Timer Listeners
    //-------------------------------------------------------------
    void attractorTimerStarted(string &val);
    void attractorTimerFinished(string &val);
    
    //-------------------------------------------------------------
    void waitOutTimerStarted(string &val);
    void waitOutTimerFinished(string &val);
    
    void videoStarted(string &id);
    void videoFinished(string &id);
    
    ofParameter <bool> bMasterControl;
    ofParameter <int> versionNo;
    ofParameter <bool> bLoad;
    
    bool bShowBoost;
    
    private:
    
    KenKenPaData data;
    
    int countDown = 3;
    Tween countDownTween;
    
    void countDownTweenStarted(string &val);
    void countDownTweenEnded(string &val);
    
    ofxCenteredTrueTypeFont bigFont;
    ofxCenteredTrueTypeFont timerFont;
    
    ofVideoPlayer_ext attractorPlayer;
    ofVideoPlayer_ext explainerPlayer;
    ofVideoPlayer_ext boostPlayer;
    ofVideoPlayer_ext rewardPlayer;
    
    Stopwatch player1Stopwatch;
    Stopwatch player2Stopwatch;
    ofImage arrow;
    
    vector <ofRectangle> positions;
    vector <ofColor> colors;
    vector <ofColor> goColors;
    int goColorsCounter;
    int counter[3] = {0,1,2};
};

#endif /* KenKenPaManager_h */
