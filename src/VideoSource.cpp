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

#ifndef TARGET_RASPBERRY_PI
void VideoSource::init(){
    video.initGrabber(1280, 720);
};
#endif
#ifdef TARGET_RASPBERRY_PI
void VideoSource::init(){
    omxCameraSettings.width = 1280;
    omxCameraSettings.height = 720;
    omxCameraSettings.framerate = 30;
    omxCameraSettings.isUsingTexture = true;
    omxCameraSettings.enablePixels = true;
    
    video.setup();
};
#endif

#ifndef TARGET_RASPBERRY_PI
void VideoSource::update(){
    video.update();
};
#endif
#ifdef TARGET_RASPBERRY_PI
void VideoSource::update(){
    return;
};
#endif

#ifndef TARGET_RASPBERRY_PI
void VideoSource::draw(){
    video.draw(ofGetWindowWidth(), 0, -ofGetWindowWidth(), ofGetWindowHeight());
};
#endif
#ifdef TARGET_RASPBERRY_PI
void VideoSource::draw(){
    video.draw();
};
#endif