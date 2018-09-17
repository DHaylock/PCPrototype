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

class Particle
{
public:
    Particle() {}
    
    Particle(ofVec2f origin,ofVec2f initVel)
    {
        this->pos = origin;
        this->vel = initVel;
        c = ofColor::fromHsb(ofRandom(0,255), 255, 255);
    }
    
    void update()
    {
        vel -= ofVec2f(0,-0.25f);
        pos += vel;
    }
    
    void draw()
    {
        ofSetColor(c);
        ofDrawRectangle(pos.x,pos.y,20,20);
    }
    
    ofVec2f pos;
    ofVec2f vel;
    ofColor c;
    bool isAlive = true;
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
                case static_cast<int>(Effects::Fountain): renderFountain(); break;
                case static_cast<int>(Effects::BlockColor): renderBlockColor(); break;
                case static_cast<int>(Effects::FadeToWhite): renderMouseEffect(); break;
                case static_cast<int>(Effects::RotatingCircles): renderMouseEffect(); break;
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
         Render the Block Color Effect
         */
        //--------------------------------------------------------------
        void renderBlockColor()
        {
            int width = ofGetWidth()/subdivision;
            int height = ofGetHeight()/subdivision;
            int ca = 0;
            
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
    
        void renderFountain()
        {
            if(ps.size() > 100)
            {
                ps.pop_back();
            }
            
            if(ofGetFrameNum() % 5 == 0)
            {
                ps.push_front(Particle(ofVec2f(ofGetWidth()/2,ofGetHeight()/4*3),ofVec2f(ofRandom(-2.5,2.5),ofRandom(-10.5,0.4))));
            }
            
            for (int i = 0; i < ps.size(); i++)
            {
                ps[i].update();
                ps[i].draw();
            }
            
        }
    
        int subdivision = 3;
        ofImage noiseTex;
        ofImage dotTex;
        ofImage ringTex;
        vector <float> randomise;
        deque <Particle> ps;
};

#endif /* DebugEffects_h */

