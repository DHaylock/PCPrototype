//
//  State.h
//  PCprototype
//
//  Created by David Haylock on 16/08/2018.
//

#ifndef State_h
#define State_h

#include <stdio.h>
#include "ofMain.h"

class State {
public:
    State();
    ~State();
    
    /**
     Constructor

     @param name State Name
     @param triggerKey State Trigger Key
     @param videofiles files
     @param imagefiles files
     */
    //--------------------------------------------------------------
    State(string name,string triggerKey,vector<string> videofiles, vector<string> imagefiles);
    
    /**
     Go to Next State
     */
    //--------------------------------------------------------------
    void nextState();
    
    /**
     Reset
     */
    //--------------------------------------------------------------
    void reset();
    
    /**
     Update
     */
    //--------------------------------------------------------------
    void update();
    
    /**
     Draw the State
     */
    //--------------------------------------------------------------
    void draw();
    
private:
    string triggerKey;
    string name;
    vector<ofImage> images;
    vector<ofVideoPlayer> videos;
    int currentState = 0;
};

#endif /* State_h */
