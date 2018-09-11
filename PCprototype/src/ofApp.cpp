#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    logSize = 25;
    
    // Setup the Gui
    gui.setup();

#ifndef TARGET_RASPBERRY_PI
//    ofSetDataPathRoot("../Resources/data/");
#else

#endif

    // Load the Configuration
    Config::instance().load();
    
    // Initialize the LED Shader
    ledProcessor.init();
    
    // Initialize the Visual Manager
    visualManager.init();
    
    // Always start with the GUI open
    bDrawGui = true;
    
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::exit()
{
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    visualManager.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    ledProcessor.startCapture();
    
    visualManager.draw();
    
    ledProcessor.endCapture();
    ledProcessor.render();
    
    if(bDrawGui)
        drawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) {
        case OF_KEY_TAB:
            bDrawGui = !bDrawGui;
            break;
        case OF_KEY_RETURN: {
            // Cycle through the modes
            if (StateManager::instance().currentMode >= 2)
            {
                StateManager::instance().currentMode = 0;
            }
            else
            {
                StateManager::instance().currentMode++;
            }
        }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::drawGui()
{
    auto mainSetting = ofxImGui::Settings();
    mainSetting.windowPos = ofVec2f(5,5);
    mainSetting.lockPosition = true;
    
    gui.begin();
    {
        if (ofxImGui::BeginWindow("pcprototype", mainSetting,false))
        {
            ImGui::Text("%.1f FPS (%.3f ms/frame)", ofGetFrameRate(), 1000.0f / ImGui::GetIO().Framerate);
            
            if(ofxImGui::BeginTree("Modes", mainSetting))
            {
                ofxImGui::AddRadio(StateManager::instance().currentMode,{"Debug","KenKenPa","Physical Toy"});
                ofxImGui::EndTree(mainSetting);
            }
            
            ofxImGui::AddGroup(ledProcessor.parameters, mainSetting);
            
            if(ofxImGui::BeginTree("Effects", mainSetting))
            {
                ofxImGui::AddRadio(StateManager::instance().currentEffect,{ "Mouse", "SpinningDots", "SpinningLines", "Noise", "Waves", "BlockColor", "FadeToWhite", "RotatingCircles", "Gradient"});
                
                ofxImGui::EndTree(mainSetting);
            }
            
            if(ofxImGui::BeginTree("KenKenPa", mainSetting))
            {
                ofxImGui::AddGroup(visualManager.parameters,mainSetting);
            
                ofxImGui::AddRadio(StateManager::instance().currentKenKenMode,{"One Player","Two Player"});
                ofxImGui::AddRadio(StateManager::instance().currentKenKenState,{"Attractor","Kiosk","Ready","Win","Reward"});
                
                ofxImGui::EndTree(mainSetting);
            }
            
            // Log Window
            if(ofxImGui::BeginTree("Logs", mainSetting))
            {
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "Logs");
                if (ImGui::SmallButton("Clear"))
                {
                    logs.clear();
                }
                ImGui::SliderInt("History Length", &logSize, 2, 100);
                
                ImGui::BeginChild("Scrolling",ImVec2(400, 250));
                for (int i = 0; i < logs.size(); i++)
                {
                    ImVec4 c(1, 1, 1, 1);
                    if(ofIsStringInString(logs[i],"[Error]"))
                    {
                        c = ImVec4(1, 0, 0, 1);
                    }
                    else if(ofIsStringInString(logs[i],"[Success]"))
                    {
                        c = ImVec4(0, 1, 0, 1);
                    }
                    else if(ofIsStringInString(logs[i],"[Status]"))
                    {
                        c = ImVec4(0, 0.5, 1, 1);
                    }
                    
                    ImGui::TextColored(c,"%s", logs[i].c_str());
                }
                ImGui::EndChild();
                ofxImGui::EndTree(mainSetting);
            }
        }
        ofxImGui::EndWindow(mainSetting);
    }
    gui.end();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    if(logs.size() > logSize)
    {
        logs.pop_back();
    }
    cout << msg.message << endl;
    logs.push_front(msg.message);
}
