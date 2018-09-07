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
     Tick
     */
    //--------------------------------------------------------------
    void update(ofEventArgs &e);
    
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
     Render the Win State
     */
    //--------------------------------------------------------------
    void renderWinState();
    
    /**
     Key Pressed Event

     @param key what key
     */
    //--------------------------------------------------------------
    void keyPressed(ofKeyEventArgs &key);
    
    // Timer Listeners
    //-------------------------------------------------------------
    void attractorTimerStarted(string &val);
    void attractorTimerFinished(string &val);
    
    //-------------------------------------------------------------
    void waitOutTimerStarted(string &val);
    void waitOutTimerFinished(string &val);

    ofParameter <int> versionNo;
    ofParameter <bool> bLoad;
    private:
    
    KenKenPaData data;
    
    int countDown = 3;
    Tween countDownTween;
    
    void countDownTweenStarted(string &val);
    void countDownTweenEnded(string &val);
    
    ofxCenteredTrueTypeFont bigFont;
    ofxCenteredTrueTypeFont timerFont;
    
    ofVideoPlayer attractorPlayer;
    ofVideoPlayer kioskPlayer;
    ofVideoPlayer rewardPlayer;
    
    Stopwatch player1Stopwatch;
    Stopwatch player2Stopwatch;
};

#endif /* KenKenPaManager_h */
