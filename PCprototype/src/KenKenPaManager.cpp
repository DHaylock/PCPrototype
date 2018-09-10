//--------------------------------------------------------------
//  KenKenPaManager.cpp
//  PCprototype
//  Created by David Haylock on 30/08/2018.
//! PCprototype
/** KenKenPaManager Class */
//-------------------------------------------------------------

#include "KenKenPaManager.h"

//-------------------------------------------------------------
void KenKenPaManager::init()
{
    ofAddListener(ofEvents().update, this, &KenKenPaManager::update);
    ofAddListener(ofEvents().keyPressed, this, &KenKenPaManager::keyPressed);
    PCMessage("KenKenPaManager", "[Success]: Ken Ken Pa Initialized");
 
    if(!bigFont.load("Fonts/Trebuchet.ttf", 80))
    {
        PCMessage("KenKenPaManager", "[Error]: Big Font Not Loaded");
    }
    
    if(!timerFont.load("Fonts/Trebuchet.ttf", 45))
    {
        PCMessage("KenKenPaManager", "[Error]: Timer Font Not Loaded");
    }
    
    data = Config::instance().getKenKenPa();
    
    versionNo.set("Version Number", 0, 0, data.versions.size()-1);
    bLoad.addListener(this, &KenKenPaManager::loadVersion);
    bLoad.set("Load Version",false);
    
    bool s = false;
    loadVersion(s);

    countDownTween.setup(0,1.0f, 5.0f, 0.1f,"Count Down");
    ofAddListener(countDownTween.tweenStarted,this,&KenKenPaManager::countDownTweenStarted);
    ofAddListener(countDownTween.tweenEnd,this,&KenKenPaManager::countDownTweenEnded);
    
    ofAddListener(attractorPlayer.videoStarted, this, &KenKenPaManager::videoStarted);
    ofAddListener(attractorPlayer.videoFinished, this, &KenKenPaManager::videoFinished);
    
    ofAddListener(kioskPlayer.videoStarted, this, &KenKenPaManager::videoStarted);
    ofAddListener(kioskPlayer.videoFinished, this, &KenKenPaManager::videoFinished);
    
    ofAddListener(rewardPlayer.videoStarted, this, &KenKenPaManager::videoStarted);
    ofAddListener(rewardPlayer.videoFinished, this, &KenKenPaManager::videoFinished);
}

//-------------------------------------------------------------
void KenKenPaManager::loadVersion(bool &val)
{
    PCMessage("KenKenPaManager", "[Wait]: Ken Ken Pa Loading New Version");
    auto it = find_if(data.versions.begin(), data.versions.end(), [&](KenKenPa const &k) {
        return k.id == versionNo;
    });
    
    // If we dont find the Quadrant
    if (it == data.versions.end())
    {
        PCMessage("KenKenPaManager", "[Error]: No Version Found");
        return;
    }
    
    int id = distance(data.versions.begin(), it);
    attractorPlayer.close();
    kioskPlayer.close();
    rewardPlayer.close();
    
    attractorPlayer.loadVideo(data.versions[id].attractorFile,"Attractor");
    attractorPlayer.setLoopState(OF_LOOP_NORMAL);
    
    kioskPlayer.loadVideo(data.versions[id].kioskFile,"Kiosk");
    kioskPlayer.setLoopState(OF_LOOP_NONE);
    
    rewardPlayer.loadVideo(data.versions[id].rewardFile,"Reward");
    rewardPlayer.setLoopState(OF_LOOP_NONE);
    bLoad = false;
    
    // Auto Run the Attractor
    attractorPlayer.playVideo();
}

//-------------------------------------------------------------
void KenKenPaManager::update(ofEventArgs &e)
{

}

//-------------------------------------------------------------
void KenKenPaManager::render()
{
    ofPushStyle();
    ofSetColor(255, 255, 255);
    switch (StateManager::instance().getKenKenState())
    {
        case static_cast<int>(KenKenState::Attractor):
        {
            attractorPlayer.draw(0, 0,ofGetWidth(), ofGetHeight());
        }
            break;
        case static_cast<int>(KenKenState::Kiosk):
        {
            kioskPlayer.draw(0, 0,ofGetWidth(), ofGetHeight());
        }
            break;
        case static_cast<int>(KenKenState::Ready):
        {
            renderReadyState();
        }
            break;
        case static_cast<int>(KenKenState::Game):
        {
            renderGameState();
        }
            break;
        case static_cast<int>(KenKenState::Reward):
        {
            rewardPlayer.draw(0, 0,ofGetWidth(), ofGetHeight());
        }
            break;
        default:
            break;
    }
    ofPopStyle();
}

//-------------------------------------------------------------
void KenKenPaManager::renderReadyState()
{
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofScale(countDownTween.getCurrentValue(), countDownTween.getCurrentValue());
    ofSetColor(255, 255, 255);
    if(countDown != 0)
        bigFont.drawStringCentered(ofToString(countDown), 0, 0);
    else
        bigFont.drawStringCentered("GO", 0, 0);
    
    ofPopMatrix();
}

//-------------------------------------------------------------
void KenKenPaManager::renderGameState()
{
    switch(StateManager::instance().getKenKenPaMode())
    {
        case static_cast<int>(KenKenMode::OnePlayer): {
            timerFont.drawStringCentered("Player 1", ofGetWidth()/2, ofGetHeight()-100);
            timerFont.drawStringCentered(ofToString(player1Stopwatch.getFormattedTime(false)), ofGetWidth()/2, ofGetHeight()-50);
        }
            break;
        case static_cast<int>(KenKenMode::TwoPlayers): {
            timerFont.drawStringCentered("Player 1", ofGetWidth()/4, ofGetHeight()-100);
            timerFont.drawStringCentered(ofToString(player1Stopwatch.getFormattedTime(false)), ofGetWidth()/4, ofGetHeight()-50);
            timerFont.drawStringCentered("Player 2" , ofGetWidth()/4*3, ofGetHeight()-100);
            timerFont.drawStringCentered(ofToString(player2Stopwatch.getFormattedTime(false)), ofGetWidth()/4*3, ofGetHeight()-50);
        }
            break;
        default:
            break;
    }
    
    
}
//-------------------------------------------------------------
void KenKenPaManager::renderEndGameState()
{

}

//-------------------------------------------------------------
void KenKenPaManager::keyPressed(ofKeyEventArgs &key)
{
    if(key.key == data.dualPlayersStartKey)
    {
        attractorPlayer.stopVideo();
        StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Kiosk);
        kioskPlayer.playVideo();
        StateManager::instance().currentKenKenMode = static_cast<int>(KenKenMode::TwoPlayers);
    }
    
    if(key.key == data.player1StartKey)
    {
        attractorPlayer.stopVideo();
        StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Kiosk);
        kioskPlayer.playVideo();
        StateManager::instance().currentKenKenMode = static_cast<int>(KenKenMode::OnePlayer);
    }
    
    if(key.key == data.player2StartKey)
    {
        attractorPlayer.stopVideo();
        StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Kiosk);
        kioskPlayer.playVideo();
        StateManager::instance().currentKenKenMode = static_cast<int>(KenKenMode::OnePlayer);
    }
    
    if(key.key == data.player1EndKey)
    {
        player1Stopwatch.stop();
    }
    
    if(key.key == data.player2EndKey)
    {
        player2Stopwatch.stop();
    }
}

//-------------------------------------------------------------
void KenKenPaManager::attractorTimerStarted(string &val)
{
    
}

//-------------------------------------------------------------
void KenKenPaManager::attractorTimerFinished(string &val)
{
    
}

//-------------------------------------------------------------
void KenKenPaManager::waitOutTimerStarted(string &val)
{
    
}

//-------------------------------------------------------------
void KenKenPaManager::waitOutTimerFinished(string &val)
{
    
}

//-------------------------------------------------------------
void KenKenPaManager::videoStarted(std::string &id)
{
    cout << id << " Started" << endl;
}

//-------------------------------------------------------------
void KenKenPaManager::videoFinished(string &id)
{
    cout << id << " Finished" << endl;
    
    if(id == "Kiosk")
    {
        StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Ready);
        countDown = 3;
        countDownTween.start();
    }
}

//-------------------------------------------------------------
void KenKenPaManager::countDownTweenStarted(string &val)
{
    cout << val << " Started " << countDown << endl;
}

//-------------------------------------------------------------
void KenKenPaManager::countDownTweenEnded(string &val)
{
    cout << val << " Ended " << countDown << endl;
    if (countDown == 0)
    {
        StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Game);
        
        if(StateManager::instance().currentKenKenMode == static_cast<int>(KenKenMode::OnePlayer))
        {
            player1Stopwatch.start();
        }
        
        if(StateManager::instance().currentKenKenMode == static_cast<int>(KenKenMode::TwoPlayers))
        {
            player1Stopwatch.start();
            player2Stopwatch.start();
        }
    }
    else
    {
        countDown--;
        countDownTween.start();
    }
}
