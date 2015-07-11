#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxHttpUtils.h"
#include "VideoSource.h"
#include "Button.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    void resetBackground();

    bool backgroundSet;
    ofPixels background;
    ofImage frame;
    ofImage currentFrame;
    string saveImageUrl;

    ofxJSONElement settings;
    string environment;
    int threshold;
    int maxRGB;
    
    VideoSource video;

    Button backgroundButton;
    Button saveImageButton;

    ofxHttpUtils httpUtils;
};
