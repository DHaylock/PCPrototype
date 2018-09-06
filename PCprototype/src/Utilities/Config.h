//--------------------------------------------------------------
//  Config.cpp
//  PCprototype
//  Created by David Haylock on 22/08/2018.
//! PCprototype
/** Config Class */
//-------------------------------------------------------------

#ifndef Config_h
#define Config_h

#include <stdio.h>
#include "ofxJSON.h"
#include "pcmain.h"

class Config {
    public:
    
        /**
         Create an Instance of the Config Manager

         @return instance
         */
        //--------------------------------------------------------------
        static Config& instance() {
            static Config * instance_ = nullptr;
            if(instance_ == nullptr)
            {
                instance_ = new Config();
                PCMessage("State Manager", "[Success]: Created Config Manager");
            }
            
            return *instance_;
        }
    
        /**
         Load the Config
         */
        //--------------------------------------------------------------
        void load();
    
    
        /**
         Return the Data for the Ken Ken Pa

         @return ken ken pa structure
         */
        //--------------------------------------------------------------
        KenKenPa getKenKenPa();
    
    private:
    
};

#endif /* Config_h */
