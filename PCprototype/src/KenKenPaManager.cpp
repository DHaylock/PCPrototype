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
    
    ofAddListener(ofEvents().keyPressed, this, &KenKenPaManager::keyPressed);
    PCMessage("KenKenPaManager", "[Success]: Ken Ken Pa Initialized");
 
    if(!bigFont.load("Fonts/Trebuchet.ttf", 80))
    {
        PCMessage("KenKenPaManager", "[Error]: Big Font Not Loaded");
    }
    
    if(!timerFont.load("Fonts/Trebuchet.ttf", 60))
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
    
    ofRemoveListener(waitOutTimer.timerStarted, this, &KenKenPaManager::waitOutTimerStarted);
    ofRemoveListener(waitOutTimer.timerFinished, this, &KenKenPaManager::waitOutTimerFinished);
    
    waitOutTimer.setup(data.versions[id].waitOutTimer, "Wait Out", false);
    
    ofAddListener(waitOutTimer.timerStarted, this, &KenKenPaManager::waitOutTimerStarted);
    ofAddListener(waitOutTimer.timerFinished, this, &KenKenPaManager::waitOutTimerFinished);
    
    ofRemoveListener(attractorTimer.timerStarted, this, &KenKenPaManager::attractorTimerStarted);
    ofRemoveListener(attractorTimer.timerFinished, this, &KenKenPaManager::attractorTimerFinished);
    
    attractorTimer.setup(data.versions[id].attractorTimer, "Attractor", false);
    
    ofAddListener(attractorTimer.timerStarted, this, &KenKenPaManager::attractorTimerStarted);
    ofAddListener(attractorTimer.timerFinished, this, &KenKenPaManager::attractorTimerFinished);
    
    // Auto Run the Attractor
    attractorPlayer.playVideo();
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
            renderRewardGameState();
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
    
    switch(StateManager::instance().currentKenKenMode)
    {
        case static_cast<int>(KenKenMode::OnePlayer):
        {
            if(player1Stopwatch.isRunning())
            {
                timerFont.drawStringCentered("Player", ofGetWidth()/2, ofGetHeight()-100);
                timerFont.drawStringCentered(ofToString(player1Stopwatch.getFormattedTime(false)), ofGetWidth()/2, ofGetHeight()-30);
            }
            else
            {
                timerFont.drawStringCentered("Calculating", ofGetWidth()/2, ofGetHeight()-100);
            }
        }
            break;
        case static_cast<int>(KenKenMode::TwoPlayers):
        {
            if(player1Stopwatch.isRunning() || player2Stopwatch.isRunning())
            {
                timerFont.drawStringCentered("Player 1", ofGetWidth()/4, ofGetHeight()-100);
                timerFont.drawStringCentered(ofToString(player1Stopwatch.getFormattedTime(false)), ofGetWidth()/4, ofGetHeight()-30);
                timerFont.drawStringCentered("Player 2" , ofGetWidth()/4*3, ofGetHeight()-100);
                timerFont.drawStringCentered(ofToString(player2Stopwatch.getFormattedTime(false)), ofGetWidth()/4*3, ofGetHeight()-30);
            }
            else
            {
                timerFont.drawStringCentered("Calculating", ofGetWidth()/2, ofGetHeight()-100);
            }
        }
            break;
        default:
            break;
    }
    
    
}
//-------------------------------------------------------------
void KenKenPaManager::renderRewardGameState()
{
    ofSetColor(255, 255, 255);
    rewardPlayer.draw(0, 0,ofGetWidth(), ofGetHeight());
    string status = "Here";
    
    switch (StateManager::instance().currentKenKenMode)
    {
        case static_cast<int>(KenKenMode::OnePlayer):
        {
            status = "Player Time " + ofToString(player1Stopwatch.getElapsedTimef());
        }
            break;
        case static_cast<int>(KenKenMode::TwoPlayers):
        {
            if(player1Stopwatch.getElapsedTimef() < player2Stopwatch.getElapsedTimef())
            {
                status = "Player 1 Wins";
            }
            else if(player1Stopwatch.getElapsedTimef() > player2Stopwatch.getElapsedTimef())
            {
                status = "Player 2 Wins";
            }
        }
            break;
            
        default:
            break;
    }

    ofSetColor(255,255,255);
    timerFont.drawStringCentered(status, ofGetWidth()/2, ofGetHeight()-100);
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
        // If it's one player stop the clock and trigger the wait out timer
        if (StateManager::instance().currentKenKenMode == static_cast<int>(KenKenMode::OnePlayer))
        {
            // Stop the clock
            player1Stopwatch.stop();
            waitOutTimer.start();
        }
        else if (StateManager::instance().currentKenKenMode == static_cast<int>(KenKenMode::TwoPlayers))
        {
            // If two player
            // Check if player two's stopwatch is running.
            // If it is stop player ones and wait
            if(player2Stopwatch.isRunning())
            {
                player1Stopwatch.stop();
            }
            else
            {
                // Other wise stop player 1s and start the wait out timer.
                player1Stopwatch.stop();
                waitOutTimer.start();
            }
        }
    
    }
    
    if(key.key == data.player2EndKey)
    {
        if (StateManager::instance().currentKenKenMode == static_cast<int>(KenKenMode::TwoPlayers))
        {
            // If two player
            // Check if player two's stopwatch is running.
            // If it is stop player ones and wait
            if(player1Stopwatch.isRunning())
            {
                player2Stopwatch.stop();
            }
            else
            {
                // Other wise stop player 1s and start the wait out timer.
                player2Stopwatch.stop();
                waitOutTimer.start();
            }
        }
    }
}

//-------------------------------------------------------------
void KenKenPaManager::attractorTimerStarted(string &val)
{
    cout << "Attractor Timer Started" << endl;
}

//-------------------------------------------------------------
void KenKenPaManager::attractorTimerFinished(string &val)
{
    cout << "Attractor Timer Finished" << endl;
    StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Attractor);
    attractorPlayer.playVideo();
    PCMessage("Ken Ken Manager", "[Status]: Starting Attractor");
}

//-------------------------------------------------------------
void KenKenPaManager::waitOutTimerStarted(string &val)
{
    cout << "Wait Out Timer Started" << endl;
}

//-------------------------------------------------------------
void KenKenPaManager::waitOutTimerFinished(string &val)
{
    cout << "Wait Out Timer Finished" << endl;
    StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Reward);
    rewardPlayer.playVideo();
    PCMessage("Ken Ken Manager", "[Status]: Starting Reward");
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
    else if (id == "Reward")
    {
        attractorTimer.start();
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
    if (countDown == 0)
    {
        StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Game);
        PCMessage("Ken Ken Manager", "[Status]: Starting Game Mode");
        
        if(StateManager::instance().currentKenKenMode == static_cast<int>(KenKenMode::OnePlayer))
        {
            player1Stopwatch.start();
            PCMessage("Ken Ken Manager", "[Status]: Starting One Player Mode");
        }
        
        if(StateManager::instance().currentKenKenMode == static_cast<int>(KenKenMode::TwoPlayers))
        {
            player1Stopwatch.start();
            player2Stopwatch.start();
            PCMessage("Ken Ken Manager", "[Status]: Starting Two Player Mode");
        }
    }
    else
    {
        countDown--;
        countDownTween.start();
    }
}
