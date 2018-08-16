#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ledProcessor.init();
    visualManager.setup();
    
    ofEnableAlphaBlending();
    setupGUI();
}

//--------------------------------------------------------------
void ofApp::setupGUI()
{
    parameters.add(ledProcessor.parameters);
    parameters.add(visualManager.parameters);
    gui.setup(parameters);
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
    
    if(showGui) {
        gui.draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == OF_KEY_TAB)
    {
        showGui = !showGui;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

