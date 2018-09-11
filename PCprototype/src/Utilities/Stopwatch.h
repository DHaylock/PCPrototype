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
#include <chrono>
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
        }
    
        /**
         Deconstructor
         */
        //-----------------------------------------------------
        ~Stopwatch()
        {
    
        }
    
        /**
         Constructor
         */
        //-----------------------------------------------------
        Stopwatch(string name)
        {
            this->name = name;
            bIsRunning = false;
        }
    
        /**
         Setup Function 
         */
        //-----------------------------------------------------
        void setup(string name)
        {
            this->name = name;
            bIsRunning = false;
            startTime = clock::now();
        }
    
        /**
         Start the Stopwatch
         */
        //-----------------------------------------------------
        void start()
        {
            startTime = clock::now();
            bIsRunning = true;
        }
    
        /**
         Stop the Stopwatch
         */
        //-----------------------------------------------------
        void stop()
        {
            endTime = clock::now();
            bIsRunning = false;
        }
    
        /**
         Get The Elapsed Time in Microseconds

         @return time
         */
        //-----------------------------------------------------
        u_int64_t getElapsedUs() const
        {
            return std::chrono::duration_cast<microseconds>(clock::now() - startTime).count();
        }
    
        /**
         Get the Elapsed Time In Milliseconds

         @return time
         */
        //-----------------------------------------------------
        u_int64_t getElapsedMs() const
        {
           return std::chrono::duration_cast<milliseconds>(clock::now() - startTime).count();
        }
    
        /**
         Get the Elapsed Time in Seconds

         @return time
         */
        //-----------------------------------------------------
        uint64_t getElapsedSec() const
        {
            return std::chrono::duration_cast<seconds>(clock::now() - startTime).count();
        }
    
        /**
         Is the Stop Watch Running

         @return boolean
         */
        //-----------------------------------------------------
        bool isRunning()
        {
            return bIsRunning;
        }
    
        /**
         Get the Elapsed Time

         @return time
         */
        //-----------------------------------------------------
        double getElapsedTimef()
        {
            std::chrono::duration<double> elapsedTime = endTime - startTime;
            return elapsedTime.count();
        }
    
        /**
         Get the Formatted Time

         @params bMins whether to return the Minutes
         @return string of time
         */
        //-----------------------------------------------------
        string getFormattedTime(bool bMins)
        {
            if(bIsRunning) {
                char buffer2[12] = " ";
                std::chrono::duration<double> elapsedTime = clock::now() - startTime;
                
                sprintf(buffer2, "%.3f", elapsedTime.count());
                return ofToString(buffer2);
            }
            else if (!bIsRunning)
            {
                std::chrono::duration<double> elapsedTime = endTime - startTime;
                char buffer2[12] = " ";
                sprintf(buffer2, "%.3f",elapsedTime);
                return ofToString(buffer2);
            }
            return "";
        }
    
    private:
    
        typedef std::chrono::steady_clock clock;
        typedef std::chrono::microseconds microseconds;
        typedef std::chrono::milliseconds milliseconds;
        typedef std::chrono::seconds seconds;
    
        std::chrono::steady_clock::time_point Restart();
    
        clock::time_point startTime;
        clock::time_point endTime;
    
        string name;
        bool bIsRunning = false;
};

#endif /* Stopwatch_h */
