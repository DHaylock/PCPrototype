//--------------------------------------------------------------
//  Tween.h
//  PCprototype
//  Created by David Haylock on 22/08/2018.
//! PCprototype
/** Tween Class */
//-------------------------------------------------------------
#ifndef Tween_h
#define Tween_h

#include "pcmain.h"

class Tween {
    public:
    
        /**
         Init Tween
         */
        //-----------------------------------------------------
        Tween()
        {
            
        }
    
        /**
         Init Tween
         */
        //-----------------------------------------------------
        Tween(int id, string tweenName)
        {
            fromValue = 0;
            toValue = 0;
            currentValue = 0;
            
            this->tweenName = tweenName;
            this->id = id;
//            ofAddListener(ofEvents().update,this,&Tween::update);
        }
    
        /**
         Init Tween
         */
        //-----------------------------------------------------
        void setup(int id,float duration, float fromValue, float toValue, string tweenName,float delay = 0.2f)
        {
            this->tweenName = tweenName;
            this->fromValue = fromValue;
            this->duration = duration;
            this->toValue = toValue;
            this->delay = delay;
            this->id = id;
            
            ofAddListener(ofEvents().update,this,&Tween::update);
        }
    
        /**
         Start a New Tween
         
         @param duration length of the tween
         @param value to which value
         */
        //-----------------------------------------------------
        void start() {
            
            initTime = ofGetElapsedTimef();
            currentValue = fromValue;
            endTime = initTime + duration;
            notified = false;
            
            ofNotifyEvent(tweenStarted,tweenName,this);
        }
    
        /**
         Auto Update Loop
         
         @param evt listener
         */
        //-----------------------------------------------------
        void update(ofEventArgs &e)
        {
            if(!notified) {
                auto now = ofGetElapsedTimef();
                currentValue = ofxeasing::map_clamp(now,
                                                    initTime,
                                                    endTime,
                                                    fromValue,
                                                    toValue,
                                                    &ofxeasing::sine::easeInOut);
            }
            
            if(fromValue > toValue)
            {
                if((currentValue <= toValue) && !notified)
                {
                    
                    notified = true; // Set notify to true before this trtigger happends
                    ofNotifyEvent(tweenEnd,tweenName,this);
                }
            }
            else if(fromValue < toValue)
            {
                if((currentValue >= toValue) && !notified)
                {
                    cout << fromValue << " " << currentValue << " " << toValue << endl;
                    notified = true; // Set notify to true before this trtigger happends
                    ofNotifyEvent(tweenEnd,tweenName,this);
                }
            }
               
            
        }
    
        /**
         Get the Current Value
         
         @return Current Value
         */
        //-----------------------------------------------------
        float getCurrentValue()
        {
            return currentValue;
        }
    
        /**
         Has the Tween Finished

         @return completed
         */
        //-----------------------------------------------------
        bool hasCompleted()
        {
            return (currentValue == toValue ? true : false);
        }
    
        ofEvent <string> tweenStarted;
        ofEvent <string> tweenEnd;
    
    private:
        
        bool notified = true;
        float duration = 0.0f;
        float toValue = 0.0f;
        float currentValue = 0.0f;
        float fromValue = 0.0f;
        float initTime = 0.0f;
        float endTime = 0.0f;
        float delay = 0.0f;
        int id;
        string tweenName;
};
#endif /* Tween_h */
