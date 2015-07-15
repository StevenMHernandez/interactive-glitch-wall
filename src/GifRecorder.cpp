#include "GifRecorder.h"

GifRecorder::GifRecorder() {
    ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &GifRecorder::imageSaved);
}

void GifRecorder::init(int _frame_count, int _nth_frame, int frameW, int frameH) {
    frame_count = _frame_count;
    nth_frame = _nth_frame;
    width = frameW;
    height = frameH;
}

void GifRecorder::update(ofImage frame) {
    if (recording == true) {
        if (frame_i % nth_frame == 0) {
            storeFrame(frame);
            saved_frame_i++;
        }
        frame_i++;
        if (saved_frame_i == frame_count) {
            recording = false;
            gifEncoder.save("image.gif");
        }
    }
}

void GifRecorder::start() {
    if(recording == false) {
        gifEncoder.reset();
        gifEncoder.setup(width, height, 0.1, 256);
        recording = true;
        frame_i = 0;
        saved_frame_i = 0;
    }
}

void GifRecorder::storeFrame(ofImage frame) {
    gifEncoder.addFrame(
        frame.getPixels(),
        frame.getWidth(),
        frame.getHeight(),
        frame.getPixelsRef().getBitsPerPixel(),
        .1f
    );
}

bool GifRecorder::isRecording() {
    return recording;
}

bool GifRecorder::isRecorded() {
    if (recorded) {
        recorded = false;
        return true;
    }
    return false;
}

void GifRecorder::imageSaved(string & fileName) {
    recorded = true;
}