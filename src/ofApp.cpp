#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    settings.open("config.json");
    environment = settings["environment"].asString();
    threshold = settings["threshold"].asInt();
    maxRGB = settings["maxRGB"].asInt();
    
    video.init();
    frame.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    if (backgroundSet) {
        ofPixels currentFramePixels;
        currentFramePixels.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
        ofPixels previousFrame;
        previousFrame.setFromPixels(frame.getPixels(), frame.getWidth(), frame.getHeight(), OF_IMAGE_COLOR);
        
        int i = 0;
        while( i < background.size()) {
            if((currentFramePixels[i+0] >= background[i+0] - threshold && currentFramePixels[i+0] <= background[i+0] + threshold) &&
               (currentFramePixels[i+1] >= background[i+1] - threshold && currentFramePixels[i+1] <= background[i+1] + threshold) &&
               (currentFramePixels[i+2] >= background[i+2] - threshold && currentFramePixels[i+2] <= background[i+2] + threshold)) {
                currentFramePixels[i+0] = previousFrame[i+0] > 0 ? previousFrame[i+0] - maxRGB : 0;
                currentFramePixels[i+1] = previousFrame[i+1] > 0 ? previousFrame[i+1] - maxRGB : 0;
                currentFramePixels[i+2] = previousFrame[i+2] > 0 ? previousFrame[i+2] - maxRGB : 0;
            }
            i += 3;
        }
        currentFrame.setFromPixels(currentFramePixels);
        frame.setFromPixels(currentFramePixels);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (!backgroundSet) {
        video.draw();
        ofDrawBitmapString("Press the space bar to set the background", 0, 20);
    } else {
        currentFrame.draw(ofGetWindowWidth(), 0, -ofGetWindowWidth(), ofGetWindowHeight());
    }
    if(environment == "development") {
        ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 0, 10);
        ofDrawBitmapString(environment, 0, 30);
    }
}

void ofApp::keyPressed(int key) {
    if(key == ' ') {
        backgroundSet = true;
        video.update();
        background.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
    }
}
