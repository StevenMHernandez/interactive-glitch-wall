#pragma once

#include "ofMain.h"

class VideoSource{
    
public:
    unsigned char* getPixels();
    int getWidth();
    int getHeight();
    void init();
    void draw();
    void update();
    
    ofVideoGrabber video;
};
