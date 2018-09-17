//--------------------------------------------------------------
//  ofVideoPlayer_ext
//  PCprototype
//  Created by David Haylock on 22/08/2018.
//! PCprototype
/** Video Player  Class */
//--------------------------------------------------------------

#ifndef ofVideoPlayer_ext_h
#define ofVideoPlayer_ext_h

#include "pcmain.h"

class ofVideoPlayer_ext: public ofVideoPlayer {
    public:

        /**
         Constructor
         */
        //--------------------------------------------------------------
        ofVideoPlayer_ext()
        {
            ofAddListener(ofEvents().update, this, &ofVideoPlayer_ext::autoUpdate);
        }
    
        /**
         Deconstructor
         */
        //--------------------------------------------------------------
        ~ofVideoPlayer_ext()
        {
            ofRemoveListener(ofEvents().update, this, &ofVideoPlayer_ext::autoUpdate);
        }
    
        /**
         Load the Track With a specified ID

         @param path where the file is
         @param trackId track identifier
         */
        //--------------------------------------------------------------
        void loadVideo(string path,string videoId)
        {
            this->videoId = videoId;
            this->loadAsync(path);
            notified = false;
        }
    
        /**
         Play The Video
         */
        //--------------------------------------------------------------
        void playVideo()
        {
            notified = false;
            ofNotifyEvent(videoStarted,this->videoId,this);
            this->play();
        }
    
        /**
         Stop The Video
         */
        //--------------------------------------------------------------
        void stopVideo()
        {
            this->stop();
        }
    
        /**
         Update the Video Player

         @param evt event listener
         */
        //--------------------------------------------------------------
        void autoUpdate(ofEventArgs &evt)
        {
            this->update();
            
            if((this->getPosition() > 0.95) && !notified) {
                ofNotifyEvent(videoFinished,this->videoId,this);
                notified = true;
            }
        }
    
        ofEvent<string> videoStarted;
        ofEvent<string> videoFinished;

    private:
        string videoId;
        bool notified;
};

#endif /* ofVideoPlayer_ext_h */
