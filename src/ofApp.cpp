#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    settings.open("config.json");
    environment = settings["environment"].asString();
    threshold = settings["threshold"].asInt();
    maxRGB = settings["maxRGB"].asInt();
    saveImageUrl = "http://localhost:" + settings["server"]["port"].asString() + "/";

    video.init();
    gifRecorder.init(settings["gif"]["frame_count"].asInt(),
                     settings["gif"]["nth_frame"].asInt(),
                     video.getWidth(),
                     video.getHeight());
    frame.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);

    backgroundButton.setPin(settings["pins"]["background"].asInt());
    saveImageButton.setPin(settings["pins"]["saveImage"].asInt());
    timer.reset();

    ofAddListener(timer.TIMER_REACHED, this, &ofApp::recordGif);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();   
    backgroundButton.update();
    saveImageButton.update();

    if (backgroundSet) {
        currentFramePixels.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
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
        gifRecorder.update(currentFrame);
        if (gifRecorder.isRecorded()) {
            uploadImage();
        }
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
    if (backgroundButton.isInitialPress()) {
        resetBackground();
    }
    if(saveImageButton.isInitialPress()) {
        saveImage();
    }
    if (timer.getTimeLeftInSeconds() > 0) {
        ofDrawBitmapStringHighlight("Recording gif in: " + ofToString((int)timer.getTimeLeftInSeconds()) + " seconds.", 10, 50);
    }
    if (gifRecorder.isRecording()) {
        ofDrawBitmapStringHighlight("Recording .gif", 10, 50);
    }
}

void ofApp::keyPressed(int key) {
    if(key == ' ') {
        resetBackground();
    }
    if(key == 's') {
        saveImage();
    }
}

void ofApp::resetBackground() {
    backgroundSet = true;
    video.update();
    background.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
    cout << "background reset.\n";
}

void ofApp::saveImage() {
    timer.reset();
    timer.setup(3999, false);
    timer.startTimer();
}

void ofApp::recordGif(ofEventArgs & eventArgs) {
    gifRecorder.start();
}

void ofApp::uploadImage() {
        httpUtils.getUrl(saveImageUrl + "?image=" + "image");
        cout << "image saved.\n";
}