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
    Particle(ofVec2f pos,ofVec2f vel,int hue)
    {
        this->pos = pos;
        this->vel = vel;
        bIsAlive = true;
        this->hue = hue;
        c.setHsb(hue,255,255);
        lifespan = 255;
    }
    
    void applyForce(ofVec2f frc)
    {
        acc += frc;
    }
    
    void update()
    {
        vel += acc;
        pos += vel;
        acc *= ofVec2f(0,0);
        
        if(lifespan > 0) {
            lifespan -= 2;
        }
        
        if(pos.y > ofGetHeight())
        {
            bIsAlive = false;
        }
    }
    
    ofVec2f getPosition()
    {
        return pos;
    }
    
    ofVec2f getVelocity()
    {
        return vel;
    }
    
    bool isAlive()
    {
        return bIsAlive;
    }
    
    void draw()
    {
        ofSetColor(c, lifespan);
        ofDrawRectangle(pos.x,pos.y,15,15);
    }
    
private:
    ofVec2f pos;
    ofVec2f acc;
    ofVec2f vel;
    int lifespan;
    bool bIsAlive;
    int hue;
    ofColor c;
};

class Firework
{
public:
    
    Firework() {}
    ~Firework() {}
    
    
    Firework(ofVec2f pos, ofVec2f vel)
    {
        hue = ofRandom(255);
        f = Particle(pos,vel,hue);
        hasExploded = false;
        bIsDead = false;
    }
    
    /**
     Explode
     */
    void explode()
    {
        hasExploded = true;
        if(!bIsDead)
        {
            for(int i = 0; i < 75; i++)
            {
                particles.push_back(Particle(
                                             f.getPosition(),
                                             ofVec2f(ofRandom(-5.5,5.5),
                                                     ofRandom(-10.5,1.5)),hue));
            }
        }
    }
    
    /**
     Has the firework moved off the screen
     
     @return flag
     */
    bool isDead()
    {
        return bIsDead;
    }
    
    /**
     Update Positions
     */
    void update()
    {
        for(int i = 0; i < particles.size(); i++)
        {
            particles[i].applyForce(ofVec2f(0,0.5));
            particles[i].update();
        }
        
        if(f.getVelocity().y >= 0.0 && !hasExploded)
        {
            this->explode();
        }
        
        f.applyForce(ofVec2f(0,0.5));
        f.update();
        if(f.getPosition().y > ofGetHeight() && !bIsDead) bIsDead = true;
    }
    
    /**
     Draw the Particles
     */
    void draw()
    {
        for(int i = 0; i < particles.size(); i++)
        {
            particles[i].draw();
        }
        
        f.draw();
    }
    
    
private:
    Particle f;
    int hue;
    deque <Particle> particles;
    bool hasExploded;
    bool bIsDead = false;
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
                case static_cast<int>(Effects::Fireworks): renderFireworks(); break;
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
            if(ps.size() > 50)
            {
                ps.pop_back();
            }
            
            if(ofGetFrameNum() % 5 == 0)
            {
                ps.push_front(Particle(ofVec2f(ofGetWidth()/2,
                                               ofGetHeight()/4*3),
                                       ofVec2f(ofRandom(-2.5,2.5),ofRandom(-25.5,-5.0)),ofRandom(255)));
            }
            
            for (int i = 0; i < ps.size(); i++)
            {
                ps[i].applyForce(ofVec2f(0,0.5));
                ps[i].update();
                ps[i].draw();
            }
        }
    
        void renderFireworks()
        {
            int s = ofRandom(-10,10);
            if (ofGetFrameNum() % (45+s) == 0)
            {
                fireworks.push_front(Firework(ofVec2f(ofGetWidth()/2+ofRandom(-ofGetWidth()/4,ofGetWidth()/4),ofGetHeight()), ofVec2f(0,ofRandom(-30,-20))));
            }
            
            if(fireworks.size() > 5) fireworks.pop_back();
            
            for (int i = 0; i < fireworks.size(); i++)
            {
                fireworks[i].update();
                fireworks[i].draw();
            }
            ofDrawBitmapString(ofToString(fireworks.size()),15,15);
        }
    
    
        int subdivision = 3;
        ofImage noiseTex;
        ofImage dotTex;
        ofImage ringTex;
        vector <float> randomise;
        deque <Particle> ps;
        deque<Firework> fireworks;
};

#endif /* DebugEffects_h */

