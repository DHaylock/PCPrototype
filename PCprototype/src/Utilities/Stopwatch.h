//--------------------------------------------------------------
//  Stopwatch.h
//  PCprototype
//  Created by David Haylock on 22/08/2018.
//! PCprototype
/** Stopwatch Class */
//--------------------------------------------------------------

#ifndef Stopwatch_h
#define Stopwatch_h

#include <sys/time.h>
#include "pcmain.h"

class Stopwatch {
    public:
    
        /**
         Constructor
         */
        //-----------------------------------------------------
        Stopwatch()
        {
            name = "Default";
            bIsRunning = false;
            ofAddListener(ofEvents().update,this,&Stopwatch::update);
        }
    
        /**
         Deconstructor
         */
        //-----------------------------------------------------
        ~Stopwatch()
        {
            ofRemoveListener(ofEvents().update,this,&Stopwatch::update);
        }
    
        /**
         Constructor
         */
        //-----------------------------------------------------
        Stopwatch(string name)
        {
            this->name = name;
            bIsRunning = false;
            ofAddListener(ofEvents().update,this,&Stopwatch::update);
        }
    
        /**
         Setup Function 
         */
        //-----------------------------------------------------
        void setup(string name)
        {
            this->name = name;
            bIsRunning = false;
            ofAddListener(ofEvents().update,this,&Stopwatch::update);
        }
    
        /**
         Start the Stopwatch
         */
        //-----------------------------------------------------
        void start()
        {
            gettimeofday(&startTime, NULL);
            bIsRunning = true;
        }
    
        /**
         Stop the Stopwatch
         */
        //-----------------------------------------------------
        void stop()
        {
            gettimeofday(&endTime, NULL);
            bIsRunning = false;
        }
    
        /**
         Event Listener for the Update

         @param e args
         */
        //-----------------------------------------------------
        void update(ofEventArgs &e)
        {
            if(bIsRunning)
            {
                timeval cuTime;
                gettimeofday(&cuTime,NULL);
                curTime.tv_sec = cuTime.tv_sec - startTime.tv_sec;
                curTime.tv_usec = cuTime.tv_usec - startTime.tv_usec;
            }
        }

        /**
         Get the Formatted Time

         @params bMins whether to return the Minutes
         @return string of time
         */
        //-----------------------------------------------------
        string getFormattedTime(bool bMins)
        {
            char buffer[8];
            
            if(bMins)
                strftime(buffer, 8, "%M:%S", localtime(&curTime.tv_sec));
            else
                strftime(buffer, 8, "%S", localtime(&curTime.tv_sec));
            int milli = abs(curTime.tv_usec) / 1000;
            
            char buffer2[12] = " ";
            sprintf(buffer2, "%s.%d", buffer, milli);
            return ofToString(buffer2);
        }
    
    private:
        timeval curTime;
        timeval startTime;
        timeval endTime;
    
        string name;
//        float startTime = 0;
//        float endTime = 0;
//        float currentTime = 0;
        bool bIsRunning = false;
};

#endif /* Stopwatch_h */
