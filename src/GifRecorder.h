#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"

class GifRecorder{
    
public:
    GifRecorder();
    void init(int, int, int, int);
    void update(ofImage);
    void start();
    bool isRecorded();
private:
    int width;
    int height;
    ofxGifEncoder gifEncoder;
    void storeFrame(ofImage);
    int frame_count;
    int nth_frame;
    int frame_i;
    int saved_frame_i;
    bool recording;
    bool recorded;
    void imageSaved(string &);
};
