#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.initGrabber(ofGetWindowWidth() / 1, ofGetWindowHeight() / 1);
    frame.setFromPixels(cam.getPixels(), cam.width, cam.height, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if (backgroundSet) {
        int i = 0;
        ofPixels currentFramePixels;
        currentFramePixels.setFromPixels(cam.getPixels(), cam.getWidth(), cam.getHeight(), OF_IMAGE_COLOR);
        ofPixels previousFrame;
        previousFrame.setFromPixels(frame.getPixels(), frame.getWidth(), frame.getHeight(), OF_IMAGE_COLOR);
        
        while( i < background.size()) {
            int threshold = 75;
            if((currentFramePixels[i+0]  >= background[i+0] - threshold && currentFramePixels[i+0]  <= background[i+0] + threshold) &&
               (currentFramePixels[i+1]  >= background[i+1] - threshold && currentFramePixels[i+1]  <= background[i+1] + threshold) &&
               (currentFramePixels[i+2]  >= background[i+2] - threshold && currentFramePixels[i+2]  <= background[i+2] + threshold)) {
                currentFramePixels[i+0] = previousFrame[i+0] > 0 ? previousFrame[i+0] - 25 : 0;
                currentFramePixels[i+1] = previousFrame[i+1] > 0 ? previousFrame[i+1] - 25 : 0;
                currentFramePixels[i+2] = previousFrame[i+2] > 0 ? previousFrame[i+2] - 25 : 0;
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
        cam.draw(ofGetWindowWidth(), 0, -ofGetWindowWidth(), ofGetWindowHeight());
        ofDrawBitmapString("Press the space bar to set the background", 0, 20);
    } else {
        currentFrame.draw(ofGetWindowWidth(), 0, -ofGetWindowWidth(), ofGetWindowHeight());
    }
    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 0, 10);
}

void ofApp::keyPressed(int key) {
    if(key == ' ') {
        backgroundSet = true;
        cam.update();
        background.setFromPixels(cam.getPixels(), cam.width, cam.height, OF_IMAGE_COLOR);
    }
}
