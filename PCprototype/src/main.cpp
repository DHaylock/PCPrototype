#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
#ifdef TARGET_OPENGLES
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
#else
    ofGLWindowSettings settings;
    settings.setGLVersion(3,2);
#endif

    settings.setSize(640,960);
    settings.windowMode = OF_FULLSCREEN;
    
    ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
