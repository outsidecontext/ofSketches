#include "testApp.h"


void testApp::setup(){
    ofSetFrameRate(0);
    ofSetVerticalSync(true);
    particles.setup();
}


void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    particles.update();
}


void testApp::draw(){
    ofBackgroundGradient(ofColor(255), ofColor(160));
    ofEnableAlphaBlending();
    particles.draw();
}

void testApp::exit(){
}


void testApp::keyPressed(int key){
    if (key=='f') {
        ofToggleFullscreen();
    }
    else if (key=='n') {
        for(int i = 0; i < particles.p.size(); i++){
            particles.p[i].flock = !particles.p[i].flock;
        }
    }
    else if (key=='m') {
        if (particles.currentMode == PARTICLE_MODE_ATTRACT)
            particles.currentMode = PARTICLE_MODE_REPEL;
        else
            particles.currentMode = PARTICLE_MODE_ATTRACT;
    }

}


void testApp::keyReleased(int key){

}


void testApp::mouseMoved(int x, int y){

}


void testApp::mouseDragged(int x, int y, int button){

}


void testApp::mousePressed(int x, int y, int button){
    particles.currentMode = PARTICLE_MODE_REPEL;
}


void testApp::mouseReleased(int x, int y, int button){
    particles.currentMode = PARTICLE_MODE_ATTRACT;
}


void testApp::windowResized(int w, int h){

}


void testApp::gotMessage(ofMessage msg){

}


void testApp::dragEvent(ofDragInfo dragInfo){ 

}