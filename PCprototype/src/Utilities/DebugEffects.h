//--------------------------------------------------------------
//  DebugEffects.h
//  PCprototype
//  Created by David Haylock on 22/08/2018.
//! PCprototype
/** DebugEffects.h Class */
//--------------------------------------------------------------

#ifndef DebugEffects_h
#define DebugEffects_h

#include "pcmain.h"

class Ring {
public:
    
    Ring() {}
    ~Ring() {}
    
    void respawn(int stageHeight,float x1,float y1,float x2,float y2) {
        
        _stageHeight = stageHeight;
        // Start at the newer mouse position
        x = x2;
        y = y2;
        
        // Intensity is just the distance between mouse points
        intensity = ofDist(x1, y1, x2, y2);
        intensity = intensity * 5;
        
        // Hue is the angle of mouse movement, scaled from -PI..PI to 0..100
        hue = ofMap(atan2(y2 - y1, x2 - x1), -PI, PI, 0, 255);
        
        // Default size is based on the screen size
        size = _stageHeight * 0.1;
    }
    
    void draw(ofImage ringImage) {
        ofPushStyle();
        // Particles fade each frame
        intensity *= 0.95;
        
        // They grow at a rate based on their intensity
        size += _stageHeight * intensity * 0.01;
        
        // If the particle is still alive, draw it
        if (intensity >= 1) {
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofColor c;
            c.setHsb(hue, 200, intensity);
            ofSetColor(c);
            ringImage.draw(x - size/2, y - size/2, size,size);
            ofDisableBlendMode();
        }
        ofPopStyle();
    }
private:
    float x, y, size, intensity, hue,_stageHeight;
};

class DebugEffects
{
    public:
    
        /**
         Create the Instance

         @return instances
         */
        //--------------------------------------------------------------
        static DebugEffects& instance() {
            static DebugEffects *instance_ = nullptr;
            if(instance_ == nullptr)
            {
                instance_ = new DebugEffects();
                PCMessage("Debug Effects", "[Success]: Created Debug Effects Manager");
            }
            
            return *instance_;
        }

        /**
         Initialize the Effects
         */
        //--------------------------------------------------------------
        void init()
        {
            dotTex.load("Textures/dot.png");
            ringTex.load("Textures/ring.png");
            noiseTex.allocate(ofGetWidth()/8, ofGetHeight()/8, OF_IMAGE_GRAYSCALE);
            subdivision = 3;
            
            for (int i = 0; i < (subdivision*subdivision); i++) {
                randomise.push_back(ofRandom(10,200));
            }
        }
    
        /**
         Draw the Effects
         */
        //--------------------------------------------------------------
        void render()
        {
            switch (StateManager::instance().currentEffect) {
                case static_cast<int>(Effects::Mouse): renderMouseEffect(); break;
                case static_cast<int>(Effects::SpinningDots): renderSpinningDots(); break;
                case static_cast<int>(Effects::SpinningLines): renderSpinningLines(); break;
                case static_cast<int>(Effects::Noise): renderNoiseTexture(); break;
                case static_cast<int>(Effects::Waves): renderWaves(); break;
                case static_cast<int>(Effects::BlockColor): renderBlockColor(); break;
                case static_cast<int>(Effects::FadeToWhite): renderMouseEffect(); break;
                case static_cast<int>(Effects::RotatingCircles): renderMouseEffect(); break;
                case static_cast<int>(Effects::Gradient): renderMouseEffect(); break;
                default: break;
            }
        }
    private:
        /**
         Draw the mouse effect
         */
        //--------------------------------------------------------------
        void renderMouseEffect()
        {
            // Mouse Circle
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofDrawCircle(ofGetMouseX(),ofGetMouseY(),10);
            ofPopStyle();
        }
    
        /**
         Draw the Spinning Dots
         */
        //--------------------------------------------------------------
        void renderSpinningDots()
        {
            int size = (ofGetWidth()+ofGetHeight())/2;
            ofPushMatrix();
            ofTranslate(0, 0);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
            ofRotateZ(ofGetElapsedTimeMillis()/10);
            ofPushMatrix();
            ofTranslate(-size,-size);
            ofEnableBlendMode(OF_BLENDMODE_SCREEN);
            ofSetColor(0, 255,20);
            dotTex.draw(size/4, size/4, size,size);
            ofSetColor(255, 0,20);
            dotTex.draw((size/4*3), size/4, size,size);
            ofSetColor(0, 0,255);
            dotTex.draw(size/4, (size/4*3), size,size);
            ofSetColor(255, 0,255);
            dotTex.draw((size/4*3),(size/4*3), size,size);
            ofDisableBlendMode();
            ofPopMatrix();
            ofPopMatrix();
            ofPopMatrix();
        }
    
        /**
         Render the Spinning Lines
         */
        //--------------------------------------------------------------
        void renderSpinningLines()
        {
            float rotationAmount = ofGetElapsedTimeMillis()/5;
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            int w = (int)(28 + 128 * sin(ofGetElapsedTimef()));
            ofDrawRectangle(ofGetWidth()/2-(w/2), ofGetHeight()/2-ofGetHeight(), w, ofGetHeight()*2);
            ofPopMatrix();
            ofPopMatrix();
        }
    
        /**
         Render the Noise Image
         */
        //--------------------------------------------------------------
        void renderNoiseTexture()
        {
            if(ofGetFrameNum() % 60 == 0) {
                for(int x = 0; x < noiseTex.getWidth(); x++) {
                    for(int y = 0; y < noiseTex.getHeight(); y++) {
                        ofColor initialColor = ofColor(255*ofNoise(x/100.0,y/100.0,ofGetElapsedTimef()),255);
                        noiseTex.setColor((int)(x+y*noiseTex.getWidth()), initialColor);
                    }
                }
                noiseTex.update();
            }
            
            ofPushMatrix();
            ofScale(8, 8);
            ofSetColor(255, 255, 255);
            noiseTex.draw(0, 0);
            ofPopMatrix();
        }
    
        /**
         Render the Waves Effect
         */
        //--------------------------------------------------------------
        void renderWaves()
        {
            float prevX = smoothX;
            float prevY = smoothY;
            smoothX += (ofGetMouseX() - smoothX) * 0.1;
            smoothY += (ofGetMouseY() - smoothY) * 0.1;
            
            // At every frame, randomly respawn one ring
            rings[int(ofRandom(100))].respawn(ofGetHeight(),prevX, prevY, smoothX, smoothY);
            
            // Give each ring a chance to redraw and update
            for (int i = 0; i < 100; i++) {
                rings[i].draw(ringTex);
            }
        }
    
        /**
         Render the Block Color Effect
         */
        //--------------------------------------------------------------
        void renderBlockColor()
        {
            
            int width = ofGetWidth()/subdivision;
            int height = ofGetHeight()/subdivision;
            
            int ca = 0;
            // Fade to full brightness then to zero
            ofPushStyle();
            for(int y = 0; y < subdivision; y++)
            {
                for(int x = 0; x < subdivision; x++)
                {
                    
                    float hue = fmodf(ofGetElapsedTimef()*randomise[ca],255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    ofDrawRectangle(x*width,y*height,width,height);
                    ca++;
                }
            }
            ofPopStyle();
        }
    
        int subdivision = 3;
        ofImage noiseTex;
        ofImage dotTex;
        ofImage ringTex;
        Ring rings[100];
        float smoothX, smoothY;
        vector <float> randomise;
    
};

#endif /* DebugEffects_h */

