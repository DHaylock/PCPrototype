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
 
    if(!bigFont.load("Fonts/Trebuchet.ttf", 80)) {
        PCMessage("KenKenPaManager", "[Error]: Big Font Not Loaded");
    }
    
    if(!timerFont.load("Fonts/Trebuchet.ttf", 25)) {
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
    
    attractorPlayer.loadAsync(data.versions[id].attractorFile);
    kioskPlayer.loadAsync(data.versions[id].kioskFile);
    rewardPlayer.loadAsync(data.versions[id].rewardFile);
    bLoad = false;
}

//-------------------------------------------------------------
void KenKenPaManager::update(ofEventArgs &e)
{

}

//-------------------------------------------------------------
void KenKenPaManager::render()
{
    ofPushStyle();
    switch (StateManager::instance().getKenKenState())
    {
        case static_cast<int>(KenKenState::Attractor):
        {
            attractorPlayer.update();
            attractorPlayer.draw(0, 0,ofGetWidth(), ofGetHeight());
        }
            break;
        case static_cast<int>(KenKenState::Kiosk):
        {
            kioskPlayer.update();
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
            rewardPlayer.update();
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
//    ofVec2f c = bigFont.
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
    timerFont.drawStringCentered("Player 1", ofGetWidth()/4, ofGetHeight()-100);
    timerFont.drawStringCentered(ofToString(player1Stopwatch.getFormattedTime(false)), ofGetWidth()/4, ofGetHeight()-75);
    timerFont.drawStringCentered("Player 2" , ofGetWidth()/4*3, ofGetHeight()-100);
    timerFont.drawStringCentered(ofToString(player2Stopwatch.getFormattedTime(false)), ofGetWidth()/4*3, ofGetHeight()-75);
}
//-------------------------------------------------------------
void KenKenPaManager::renderEndGameState()
{

}

//-------------------------------------------------------------
void KenKenPaManager::keyPressed(ofKeyEventArgs &key)
{
    if(key.key == ' ')
    {
        countDown = 3;
        countDownTween.start();
    }
    
    if(key.key == data.player1StartKey) player1Stopwatch.start();
    if(key.key == data.player2StartKey) player2Stopwatch.start();
    if(key.key == data.player1EndKey) player1Stopwatch.stop();
    if(key.key == data.player2EndKey) player2Stopwatch.stop();
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
        player1Stopwatch.start();
        player2Stopwatch.start();
    }
    else
    {
        countDown--;
        
        countDownTween.start();
    }
}
