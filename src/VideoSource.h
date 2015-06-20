#pragma once

#include "ofMain.h"

#ifdef TARGET_RASPBERRY_PI
    #include "ofxRPiCameraVideoGrabber.h"
#endif

class VideoSource{
    
public:
    unsigned char* getPixels();
    int getWidth();
    int getHeight();
    void init();
    void draw();
    void update();
    
#ifndef TARGET_RASPBERRY_PI
    ofVideoGrabber video;
#endif
#ifdef TARGET_RASPBERRY_PI
    ofxRPiCameraVideoGrabber video;
    OMXCameraSettings omxCameraSettings;
#endif

};