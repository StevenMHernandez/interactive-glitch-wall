#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
    
        void keyPressed(int key);

        ofVideoGrabber cam;
        bool backgroundSet;
        ofPixels background;
        ofImage frame;
        ofImage currentFrame;

};