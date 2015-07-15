#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxHttpUtils.h"
#include "ofxTimer.h"
#include "VideoSource.h"
#include "Button.h"
#include "GifRecorder.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    void resetBackground();
    void saveImage();
    void recordGif(ofEventArgs&);
    void uploadImage();

    bool backgroundSet;
    ofPixels background;
    ofImage frame;
    ofImage currentFrame;
    string saveImageUrl;

    ofPixels currentFramePixels;
    ofPixels previousFrame;

    ofxJSONElement settings;
    string environment;
    int threshold;
    int maxRGB;
    
    VideoSource video;

    Button backgroundButton;
    Button saveImageButton;

    ofxHttpUtils httpUtils;

    GifRecorder gifRecorder;

    ofxTimer timer;
};
