#include "VideoSource.h"

unsigned char* VideoSource::getPixels(){
    return video.getPixels();
};

int VideoSource::getWidth(){
    return video.getWidth();
};

int VideoSource::getHeight(){
    return video.getHeight();
};

void VideoSource::init(){
    video.initGrabber(320, 240);
};

void VideoSource::update(){
    video.update();
};

void VideoSource::draw(){
    video.draw(ofGetWindowWidth(), 0, -ofGetWindowWidth(), ofGetWindowHeight());
};
