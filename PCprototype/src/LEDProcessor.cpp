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
    shader.load("Shaders/LED_ES2/LED");
#else
    if(ofIsGLProgrammableRenderer()){
        shader.load("Shaders/LED_GL3/LED");
    }else{
        shader.load("Shaders/LED_GL2/LED");
    }
#endif
    
    shaderBuffer.allocate(ofGetWidth(), ofGetHeight());
    shaderBuffer.begin();
        ofClear(0, 0, 0);
    shaderBuffer.end();
    
    parameters.setName("LED Simulator");
    parameters.add(active.set("Shader Active", true));
    parameters.add(pixelSize.set("Pixel Size", 15, 2, 75));
    parameters.add(vignetteAmount.set("Vignette Amount", 0, 0, 1));
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
        shader.setUniform1f("vignetteAmount", vignetteAmount);
        ofClear(0, 0, 0);
    }
    
    shaderBuffer.draw(0,0);
    
    if(active) {
        shader.end();
        shaderBuffer.getTexture().unbind();
    }
}
