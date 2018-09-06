#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetDataPathRoot("../Resources/data/");
    ledProcessor.init();
    visualManager.setup();
    
    ofEnableAlphaBlending();
    setupGUI();
}

//--------------------------------------------------------------
void ofApp::setupGUI()
{
    openRoot.setup("Open Root Folder");
    openRoot.addListener(this, &ofApp::openRootFolder);
 
    reloadContent.setup("Load New Content");
    reloadContent.addListener(this, &ofApp::loadNewContent);
    
    parameters.add(openRoot.getParameter());
    parameters.add(reloadContent.getParameter());
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

//--------------------------------------------------------------
void ofApp::openRootFolder()
{
    ofSystem("open ./data/");
}

//--------------------------------------------------------------
void ofApp::loadNewContent()
{
    cout << "Loading New Content" << endl;
    visualManager.reloadContent();
}

