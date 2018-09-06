//
//  LEDProcessor.cpp
//  PCprototype
//
//  Created by David Haylock on 14/08/2018.
//

#include "LEDProcessor.h"

//--------------------------------------------------------------
void LEDProcessor::init()
{
#ifdef TARGET_OPENGLES
    if(!shader.load("Shaders/LED_ES2/LED"))
    {
        PCMessage("LEDProcessor", "[Error]: ES2 Shader Not Loaded");
    }
    else
    {
        PCMessage("LEDProcessor", "[Success]: Shader Loaded for ES2");
    }
#else
    if(ofIsGLProgrammableRenderer())
    {
        if(!shader.load("Shaders/LED_GL3/LED"))
        {
            PCMessage("LEDProcessor", "[Error]: GL3 Shader Not Loaded");
        }
        else
        {
            PCMessage("LEDProcessor", "[Success]: Shader Loaded for GL3");
        }
    }
    else
    {
        if(!shader.load("Shaders/LED_GL2/LED"))
        {
            PCMessage("LEDProcessor", "[Error]: GL2 Shader Not Loaded");
        }
        else
        {
            PCMessage("LEDProcessor", "[Success]: Shader Loaded for GL2");
        }
    }
#endif
    
    shaderBuffer.allocate(ofGetWidth(), ofGetHeight());
    shaderBuffer.begin();
        ofClear(0, 0, 0);
    shaderBuffer.end();
    string ss = "[Success]: Setting Frame Buffer to " + ofToString(shaderBuffer.getWidth()) + "x" + ofToString(shaderBuffer.getHeight());
    PCMessage("LEDProcessor", ss.c_str());
    
    parameters.setName("LED Simulator");
    parameters.add(active.set("Shader Active", true));
    parameters.add(pixelSize.set("Pixel Size", 15, 2, 75));
    parameters.add(tintColor.set(ofColor::white));
}

//--------------------------------------------------------------
void LEDProcessor::startCapture()
{
    shaderBuffer.begin();
    ofClear(0, 0, 0);
}

//--------------------------------------------------------------
void LEDProcessor::endCapture()
{
    shaderBuffer.end();
}

//--------------------------------------------------------------
void LEDProcessor::render()
{
    if(active) {
        shaderBuffer.getTexture().bind();
        shader.begin();
        shader.setUniform1f("pixelSize", pixelSize);
        shader.setUniform2f("resolution", ofVec2f(ofGetWidth(), ofGetHeight()));
        shader.setUniform4f("tintColor", tintColor);
        ofClear(0, 0, 0);
    }
    
    shaderBuffer.draw(0,0);
    
    if(active) {
        shader.end();
        shaderBuffer.getTexture().unbind();
    }
}
