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
    
    bMasterControl.set("Master Control", false);
    versionNo.set("Version Number", 0, 0, data.versions.size()-1);
    bLoad.addListener(this, &KenKenPaManager::loadVersion);
    bLoad.set("Load Version",false);
    
    bool s = true;
    
    bShowBoost = false;
    loadVersion(s);

    countDownTween.setup(0,1.0f, 5.0f, 0.1f,"Count Down");
    ofAddListener(countDownTween.tweenStarted,this,&KenKenPaManager::countDownTweenStarted);
    ofAddListener(countDownTween.tweenEnd,this,&KenKenPaManager::countDownTweenEnded);
    
    ofAddListener(attractorPlayer.videoStarted, this, &KenKenPaManager::videoStarted);
    ofAddListener(attractorPlayer.videoFinished, this, &KenKenPaManager::videoFinished);
    
    ofAddListener(explainerPlayer.videoStarted, this, &KenKenPaManager::videoStarted);
    ofAddListener(explainerPlayer.videoFinished, this, &KenKenPaManager::videoFinished);
    
    ofAddListener(rewardPlayer.videoStarted, this, &KenKenPaManager::videoStarted);
    ofAddListener(rewardPlayer.videoFinished, this, &KenKenPaManager::videoFinished);
    
    ofAddListener(boostPlayer.videoStarted, this, &KenKenPaManager::videoStarted);
    ofAddListener(boostPlayer.videoFinished, this, &KenKenPaManager::videoFinished);
    
    boostPlayer.loadVideo(data.boostFile1,"Boost 1");
    
    arrow.load("Textures/white-arrow.png");
    
    positions.push_back(ofRectangle(90,150,arrow.getWidth()/4*3,arrow.getHeight()/4*3));
    positions.push_back(ofRectangle(-50,50,arrow.getWidth()/4*3,arrow.getHeight()/4*3));
    positions.push_back(ofRectangle(-190,170,arrow.getWidth()/4*3,arrow.getHeight()/4*3));
    
    positions.push_back(ofRectangle(90,370,arrow.getWidth()/4*3,arrow.getHeight()/4*3));
    positions.push_back(ofRectangle(-50,270,arrow.getWidth()/4*3,arrow.getHeight()/4*3));
    positions.push_back(ofRectangle(-190,390,arrow.getWidth()/4*3,arrow.getHeight()/4*3));
    
    positions.push_back(ofRectangle(90,590,arrow.getWidth()/4*3,arrow.getHeight()/4*3));
    positions.push_back(ofRectangle(-50,490,arrow.getWidth()/4*3,arrow.getHeight()/4*3));
    positions.push_back(ofRectangle(-190,610,arrow.getWidth()/4*3,arrow.getHeight()/4*3));
    
    colors.push_back(ofColor(0,29,245));
    colors.push_back(ofColor(215,49,137));
    colors.push_back(ofColor(225,109,56));

    boostPlayer.setLoopState(OF_LOOP_NORMAL);
}

//-------------------------------------------------------------
void KenKenPaManager::loadVersion(bool &val)
{
    if(val)
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
        explainerPlayer.close();
        rewardPlayer.close();
        
        attractorPlayer.loadVideo(data.versions[id].attractorFile,"Attractor");
        attractorPlayer.setLoopState(OF_LOOP_NORMAL);
        
        explainerPlayer.loadVideo(data.versions[id].kioskFile,"Kiosk");
        explainerPlayer.setLoopState(OF_LOOP_NORMAL);
        
        rewardPlayer.loadVideo(data.versions[id].rewardFile,"Reward");
        rewardPlayer.setLoopState(OF_LOOP_NORMAL);
        
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
        case static_cast<int>(KenKenState::Explainer):
        {
            explainerPlayer.draw(0, 0,ofGetWidth(), ofGetHeight());
        }
            break;
        case static_cast<int>(KenKenState::Countdown):
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
    
    if(boostPlayer.isLoaded() && boostPlayer.isPlaying() && bShowBoost)
    {
        ofSetColor(255, 255, 255);
        boostPlayer.draw(0, 0,ofGetWidth(), ofGetHeight());
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
    float direction = 0;
    switch (StateManager::instance().currentKenKenMode)
    {
        case static_cast<int>(KenKenMode::OnePlayer):
        {
            status = "Player Time " + ofToString(player1Stopwatch.getFormattedTime(false));
        }
            break;
        case static_cast<int>(KenKenMode::TwoPlayers):
        {
            if(player1Stopwatch.getElapsedTimef() < player2Stopwatch.getElapsedTimef())
            {
                status = "Player 1 Wins";
                direction = -0.7;
            }
            else if(player1Stopwatch.getElapsedTimef() > player2Stopwatch.getElapsedTimef())
            {
                status = "Player 2 Wins";
                direction = 0.7;
            }
        }
            break;
            
        default:
            break;
    }

    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,0);
    ofScale(direction, 1.2);

    if(ofGetFrameNum() % 30 == 0)
    {
        counter[0]++;
        counter[1]++;
        counter[2]++;
    }
    
    for(int i = 0; i < 3; i++) {
        if(counter[i] >= colors.size())
        {
            counter[i] = 0;
        }
    }
    
    for (int i = 0; i < positions.size()-2; i+=3)
    {
        ofSetColor(colors[counter[0]]);
        arrow.draw(positions[i].x, positions[i].y,positions[i].width,positions[i].height);
        ofSetColor(colors[counter[1]]);
        arrow.draw(positions[i+1].x, positions[i+1].y,positions[i+1].width,positions[i+1].height);
        ofSetColor(colors[counter[2]]);
        arrow.draw(positions[i+2].x, positions[i+2].y,positions[i+2].width,positions[i+2].height);
    }
    ofPopMatrix();
    
    ofSetColor(255,255,255);
    timerFont.drawStringCentered(status, ofGetWidth()/2, ofGetHeight()-100);
}

//-------------------------------------------------------------
void KenKenPaManager::allStop()
{
    StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Attractor);
    explainerPlayer.stopVideo();
    boostPlayer.stopVideo();
    rewardPlayer.stopVideo();
    player1Stopwatch.stop();
    player2Stopwatch.stop();
    waitOutTimer.invalidate();
    attractorTimer.invalidate();
}

//-------------------------------------------------------------
void KenKenPaManager::setAttractorMode()
{
    allStop();
    attractorPlayer.playVideo();
}

//-------------------------------------------------------------
void KenKenPaManager::setExplainerMode()
{
    allStop();
    StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Explainer);
    explainerPlayer.playVideo();
}

//-------------------------------------------------------------
void KenKenPaManager::setCountdownMode()
{
    allStop();
    StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Countdown);
    countDown = 3;
    countDownTween.start();
}

//-------------------------------------------------------------
void KenKenPaManager::setGameMode()
{
    StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Game);
    player1Stopwatch.start();
    player2Stopwatch.start();
}

//-------------------------------------------------------------
void KenKenPaManager::setRewardMode()
{
    StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Reward);
    player1Stopwatch.stop();
    player2Stopwatch.stop();
    rewardPlayer.playVideo();
}

//-------------------------------------------------------------
void KenKenPaManager::keyPressed(ofKeyEventArgs &key)
{
    if(key.key == data.pK.dualPlayersStartKey)
    {
        if(StateManager::instance().currentKenKenState == static_cast<int>(KenKenState::Attractor))
        {
            attractorPlayer.stopVideo();
            StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Explainer);
            explainerPlayer.playVideo();
            StateManager::instance().currentKenKenMode = static_cast<int>(KenKenMode::TwoPlayers);
        }
    }
    
    if(key.key == data.pK.player1StartKey)
    {
        if(StateManager::instance().currentKenKenState == static_cast<int>(KenKenState::Attractor))
        {
            attractorPlayer.stopVideo();
            StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Explainer);
            explainerPlayer.playVideo();
            StateManager::instance().currentKenKenMode = static_cast<int>(KenKenMode::OnePlayer);
        }
    }
    
    if(key.key == data.pK.player2StartKey)
    {
        if(StateManager::instance().currentKenKenState == static_cast<int>(KenKenState::Attractor))
        {
            attractorPlayer.stopVideo();
            StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Explainer);
            explainerPlayer.playVideo();
            StateManager::instance().currentKenKenMode = static_cast<int>(KenKenMode::OnePlayer);
        }
    }
    
    if(key.key == data.pK.player1EndKey)
    {
        if(StateManager::instance().currentKenKenState == static_cast<int>(KenKenState::Game))
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
    
    }
    
    if(key.key == data.pK.player2EndKey)
    {
        if(StateManager::instance().currentKenKenState == static_cast<int>(KenKenState::Game))
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
    
    if(key.key == data.mK.allStopKey) allStop();
    if(key.key == data.mK.attractorModeKey) setAttractorMode();
    if(key.key == data.mK.explainerModeKey) setExplainerMode();
    if(key.key == data.mK.countdownModeKey) setCountdownMode();
    if(key.key == data.mK.gameModeKey) setGameMode();
    if(key.key == data.mK.winModeKey) setRewardMode();
    
    if(key.key == data.boost1StartKey)
    {
//        boostPlayer.close();
        boostPlayer.loadVideo(data.boostFile1, "Boost 1");
        boostPlayer.playVideo();
        bShowBoost = true;
    }
    
    if(key.key == data.boost2StartKey)
    {
//        boostPlayer.close();
        boostPlayer.loadVideo(data.boostFile2, "Boost 2");
        boostPlayer.playVideo();
        boostPlayer.setLoopState(OF_LOOP_NORMAL);

        bShowBoost = true;
    }
    
    if(key.key == data.boost3StartKey)
    {
//        boostPlayer.close();
        boostPlayer.loadVideo(data.boostFile3, "Boost 3");
        boostPlayer.playVideo();
        boostPlayer.setLoopState(OF_LOOP_NORMAL);
        bShowBoost = true;
    }
    
    if(key.key == data.boost4StartKey)
    {
//        boostPlayer.close();
        boostPlayer.loadVideo(data.boostFile4, "Boost 4");
        boostPlayer.playVideo();
        boostPlayer.setLoopState(OF_LOOP_NORMAL);

        bShowBoost = true;
    }

    if(key.key == 'l')
    {
	boostPlayer.stopVideo();
	bShowBoost = false;
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
    
/*    if(id == "Kiosk")
    {
        StateManager::instance().currentKenKenState = static_cast<int>(KenKenState::Countdown);
        countDown = 3;
        countDownTween.start();
    }
    else if (id == "Reward")
    {
        attractorTimer.start();
    }
    if(ofIsStringInString(id, "Boost"))
    {
        bShowBoost = false;
    }*/
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
