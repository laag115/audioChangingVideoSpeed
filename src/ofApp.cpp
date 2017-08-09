#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // initialize soundStream
    soundStream.printDeviceList();
    int outChannels = 0;
    int inChannels = 2;
    int sampleRate = 44100;
    int bufferSize = 256;
    int nBuffers = 4;
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);

    soundStream.setup(this, outChannels, inChannels, sampleRate, bufferSize, nBuffers);

    // initialize volume variables
    bufferCounter = 0;
    // curVol = 0;
    smoothedVol = 0.0;
    scaledVol = 0.0;

    // load and play video
    video.load("/movies/Euphoria-short.mp4");
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    scaledVol = ofMap(smoothedVol, 0.0, 0.10, 0.0, .20, true);
    if (scaledVol > .15)
        video.setSpeed(1.0-scaledVol);
}

//--------------------------------------------------------------
void ofApp::draw(){
    video.draw(0,0, ofGetWidth(), ofGetHeight());
    ofDrawBitmapString("scaledvol: " + ofToString(scaledVol), 32, 32);

}

void ofApp::audioIn(float* input, int bufferSize, int nChannels){

    float curVol = 0.0;

    // samples are "interleaved"
    int numCounted = 0;

    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i] = input[i*2]*0.5;
        right[i] = input[i*2+1];
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }

    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;

    // this is how we get the root of rms :)
    curVol = sqrt( curVol );

    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;

    bufferCounter++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
