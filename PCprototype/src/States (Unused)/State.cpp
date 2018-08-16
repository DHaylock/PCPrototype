//
//  State.cpp
//  PCprototype
//
//  Created by David Haylock on 16/08/2018.
//

#include "State.h"



//--------------------------------------------------------------
State::State()
{
    // Construct
}

//--------------------------------------------------------------
State::~State()
{
    // Deconstruct
}

//--------------------------------------------------------------
State::State(string name,string triggerKey,vector<string> videofiles, vector<string> imagefiles)
{
    
}

//--------------------------------------------------------------
void State::nextState()
{
    currentState++;
}

//--------------------------------------------------------------
void State::reset()
{
    currentState = 0;
}

//--------------------------------------------------------------
void State::update()
{
    
}

//--------------------------------------------------------------
void State::draw()
{
    
}

