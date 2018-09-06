//
//  VisualManager.cpp
//  PCprototype
//
//  Created by David Haylock on 15/08/2018.
//

#include "VisualManager.h"


//--------------------------------------------------------------
void VisualManager::reloadContent()
{
    loadVideos();
    loadImages();
}

//--------------------------------------------------------------
void VisualManager::init()
{
    keymap.insert(pair<char,int>('0',0));
    keymap.insert(pair<char,int>('1',1));
    keymap.insert(pair<char,int>('2',2));
    keymap.insert(pair<char,int>('3',3));
    keymap.insert(pair<char,int>('4',4));
    keymap.insert(pair<char,int>('5',5));
    keymap.insert(pair<char,int>('6',6));
    keymap.insert(pair<char,int>('7',7));
    keymap.insert(pair<char,int>('8',8));
    keymap.insert(pair<char,int>('9',9));
    keymap.insert(pair<char,int>('q',10));
    keymap.insert(pair<char,int>('w',11));
    keymap.insert(pair<char,int>('e',12));
    keymap.insert(pair<char,int>('r',13));
    keymap.insert(pair<char,int>('t',14));
    keymap.insert(pair<char,int>('y',15));
    keymap.insert(pair<char,int>('u',16));
    keymap.insert(pair<char,int>('i',17));
    keymap.insert(pair<char,int>('o',18));
    keymap.insert(pair<char,int>('p',19));
    keymap.insert(pair<char,int>('a',20));
    keymap.insert(pair<char,int>('s',21));
    keymap.insert(pair<char,int>('d',22));
    keymap.insert(pair<char,int>('f',23));
    keymap.insert(pair<char,int>('g',24));
    keymap.insert(pair<char,int>('h',25));
    keymap.insert(pair<char,int>('j',26));
    keymap.insert(pair<char,int>('k',27));
    keymap.insert(pair<char,int>('l',28));
    keymap.insert(pair<char,int>('z',29));
    keymap.insert(pair<char,int>('x',30));
    keymap.insert(pair<char,int>('c',31));
    keymap.insert(pair<char,int>('v',32));
    keymap.insert(pair<char,int>('b',33));
    keymap.insert(pair<char,int>('n',34));
    keymap.insert(pair<char,int>('m',35));
    keymap.insert(pair<char,int>('!',36));
    keymap.insert(pair<char,int>('@',37));
    keymap.insert(pair<char,int>('~',38));
    keymap.insert(pair<char,int>('$',39));
    keymap.insert(pair<char,int>('%',40));
    keymap.insert(pair<char,int>('^',41));
    keymap.insert(pair<char,int>('&',42));
    keymap.insert(pair<char,int>('*',43));
    keymap.insert(pair<char,int>('(',44));
    keymap.insert(pair<char,int>(')',45));
    keymap.insert(pair<char,int>('_',46));
    keymap.insert(pair<char,int>('+',47));
    keymap.insert(pair<char,int>('-',48));
    keymap.insert(pair<char,int>('=',49));
    keymap.insert(pair<char,int>('{',50));
    keymap.insert(pair<char,int>('}',51));
    keymap.insert(pair<char,int>('[',52));
    keymap.insert(pair<char,int>(']',53));
    
    reloadContent();
    
    ofAddListener(ofEvents().keyPressed, this, &VisualManager::keyPress);
    parameters.setName("Visual Manager");
    parameters.add(mode.set("Mode",false));
    parameters.add(currentVideo.set("Current Video", 0, 0, videos.size()));
    parameters.add(currentImage.set("Current Image", 0, 0, images.size()));
}

//--------------------------------------------------------------
void VisualManager::loadImages()
{
    loader.stopThread();
    
    images.clear();
    ofDirectory dir("Images");
    dir.sort();
    
    images.resize(dir.size());
    
    for (int i = 0; i < (int)dir.size(); i++) {
        loader.loadFromDisk(images[i], dir.getPath(i));
    }
}

//--------------------------------------------------------------
void VisualManager::loadVideos()
{
    videos.clear();
    ofDirectory dir("Videos");
    dir.sort();
    
    for (int i = 0; i < (int)dir.size(); i++) {
        ofVideoPlayer player;
        player.load(dir.getPath(i));
        player.setLoopState(OF_LOOP_NORMAL);
        videos.push_back(player);
    }
}

//--------------------------------------------------------------
void VisualManager::update()
{
    for (int i = 0; i < videos.size(); i++) {
        videos[i].update();
    }
}

//--------------------------------------------------------------
void VisualManager::draw()
{
    if (mode) {
        if (!videos.empty()) {
            if (videos.size() > currentVideo) {
                videos[currentVideo].draw(0,0,ofGetWidth(),ofGetHeight());
            }
        }
    }
    else {
        if(!images.empty()) {
            if (images.size() > currentImage) {
                images[currentImage].draw(0,0);
            }
        }
    }
}

//--------------------------------------------------------------
void VisualManager::keyPress(ofKeyEventArgs &key)
{
//    if(key.key == OF_KEY_TAB || key.key == OF_KEY_RETURN || key.key == OF_KEY_LEFT_SHIFT || key.key == OF_KEY_RIGHT_SHIFT) {
//        
//        if(key.key == OF_KEY_RETURN) {
//            mode = !mode;
//        }
//        return;
//    }
//    else {
//        if(keymap.count((char)key.key) > 0) {
//            if (mode) {
//                currentVideo = keymap.at((char)key.key);
//                if (videos.size() > currentVideo) {
//                    videos[currentVideo].setPosition(0.0);
//                    videos[currentVideo].play();
//                }
//            }
//            else {
//                currentImage = keymap.at((char)key.key);
//            }
////            cout << key.key << " " << (char)key.key << endl;
//        }
//        else {
//            cout << "Invalid Action" << endl;
//            return;
//        }
//    }
}

