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
    shader.load("LED/LED");
    
    shaderBuffer.allocate(ofGetWidth(), ofGetHeight());
    shaderBuffer.begin();
        ofClear(0, 0, 0);
    shaderBuffer.end();
    
    parameters.setName("LED Simulator");
    parameters.add(active.set("Shader Active", true));
    parameters.add(pixelSize.set("Pixel Size", 10, 2, 100));
    parameters.add(resolutionW.set("Resolution Width", ofGetWidth(), 0, ofGetWidth()));
    parameters.add(resolutionH.set("Resolution Height", ofGetHeight(), 0, ofGetHeight()));
    parameters.add(overlayColor.set(ofColor::white));
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
        shader.setUniform4f("overlay", overlayColor);
        ofClear(0, 0, 0);
    }
    
    shaderBuffer.draw(0,0);
    
    if(active) {
        shader.end();
        shaderBuffer.getTexture().unbind();
    }
}
