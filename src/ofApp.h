#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "VideoSource.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    bool backgroundSet;
    ofPixels background;
    ofImage frame;
    ofImage currentFrame;

    ofxJSONElement settings;
    string environment;
    int threshold;
    int maxRGB;
    
    VideoSource video;
    
};