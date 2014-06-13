#include "testApp.h"


void testApp::setup() {
	//ofEnableDepthTest();
    
	vidGrabber.initGrabber(320/2, 240/2);
    // int width, int height, double pyramidScale, int pyramidLevels, int windowSize,
    // int iterationsPerLevel, int expansionArea, double expansionSigma, bool flowFeedback, bool gaussianFiltering
	flowSolver.setup(vidGrabber.getWidth(), vidGrabber.getHeight(), 0.35, 5, 10, 1, 3, 2.25, false, false);
    flowSolver.setMirror(true, false);
	ofEnableAlphaBlending();
    
    flowScale.x = (float)ofGetWidth() / (float)vidGrabber.getWidth();
    flowScale.y = (float)ofGetHeight() / (float)vidGrabber.getHeight();
    ofLogNotice() << "scale x: " << flowScale.x;

	for(int i=0; i<N_CELLS; i++) {
		rotation[i] = 0;
	}
    
    particles.setup();
    
    OFX_REMOTEUI_SERVER_SETUP();
    //OFX_REMOTEUI_SERVER_SET_CALLBACK(testApp::serverCallback);
    OFX_REMOTEUI_SERVER_SHARE_PARAM(flowForce, 0, 10);
    //OFX_REMOTEUI_SERVER_SHARE_COLOR_PARAM(color);
    //load values from XML, as they were last saved (if they were)
    OFX_REMOTEUI_SERVER_LOAD_FROM_XML();
    
}


void testApp::update() {
	ofSetWindowTitle(ofToString(ofGetFrameRate())+"fps");
    
	vidGrabber.update();
	if(vidGrabber.isFrameNew()) {
		flowSolver.update(vidGrabber);
	}
    
    for (int i=0; i < particles.p.size(); i++) {
        Particle * p = &particles.p[i];
        ofPoint force = flowSolver.getVelAtPixel(p->pos.x/flowScale.x, p->pos.y/flowScale.y);
        if (force.length() > 1 || force.length() < -1) {
            p->externalForce = force * flowForce;
            //ofLogNotice() << "force at " << p->pos.x << "," << p->pos.y << " is: " << force.length();
        }
        
    }
    
    particles.update();
    
}


void testApp::draw() {
    ofBackgroundGradient(ofColor(255), ofColor(160));
	ofSetColor(255, 255, 255);
    if (ofGetKeyPressed('d')) {
        //vidGrabber.draw(0, 0, ofGetWidth(), ofGetHeight());
        flowSolver.drawColored(ofGetWidth(), ofGetHeight(), 10, 3);
    }
    particles.draw();
}


void testApp::keyPressed(int key) {
    
}


void testApp::keyReleased(int key) {
	if(key == 'p') { flowSolver.setPyramidScale(ofClamp(flowSolver.getPyramidScale() - 0.01,0.0,1.0)); }
	else if(key == 'P') { flowSolver.setPyramidScale(ofClamp(flowSolver.getPyramidScale() + 0.01,0.0,1.0)); }
	else if(key == 'l') { flowSolver.setPyramidLevels(MAX(flowSolver.getPyramidLevels() - 1,1)); }
	else if(key == 'L') { flowSolver.setPyramidLevels(flowSolver.getPyramidLevels() + 1); }
	else if(key == 'w') { flowSolver.setWindowSize(MAX(flowSolver.getWindowSize() - 1,1)); }
	else if(key == 'W') { flowSolver.setWindowSize(flowSolver.getWindowSize() + 1); }
	else if(key == 'i') { flowSolver.setIterationsPerLevel(MAX(flowSolver.getIterationsPerLevel() - 1,1)); }
	else if(key == 'I') { flowSolver.setIterationsPerLevel(flowSolver.getIterationsPerLevel() + 1); }
	else if(key == 'a') { flowSolver.setExpansionArea(MAX(flowSolver.getExpansionArea() - 2,1)); }
	else if(key == 'A') { flowSolver.setExpansionArea(flowSolver.getExpansionArea() + 2); }
	else if(key == 's') { flowSolver.setExpansionSigma(ofClamp(flowSolver.getExpansionSigma() - 0.01,0.0,10.0)); }
	else if(key == 'S') { flowSolver.setExpansionSigma(ofClamp(flowSolver.getExpansionSigma() + 0.01,0.0,10.0)); }
	//else if(key == 'f') { flowSolver.setFlowFeedback(false); }
	//else if(key == 'F') { flowSolver.setFlowFeedback(true); }
	else if(key == 'g') { flowSolver.setGaussianFiltering(false); }
	else if(key == 'G') { flowSolver.setGaussianFiltering(true); }
    
    else if (key=='f') {
        ofToggleFullscreen();
        flowScale.x = (float)ofGetWidth() / (float)vidGrabber.getWidth();
        flowScale.y = (float)ofGetHeight() / (float)vidGrabber.getHeight();
        ofLogNotice() << "scale x: " << flowScale.x;
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


void testApp::mouseMoved(int x, int y ) {

}


void testApp::mouseDragged(int x, int y, int button) {

}


void testApp::mousePressed(int x, int y, int button) {
    particles.currentMode = PARTICLE_MODE_REPEL;
}


void testApp::mouseReleased(int x, int y, int button) {
    particles.currentMode = PARTICLE_MODE_ATTRACT;
}


void testApp::windowResized(int w, int h) {

}


void testApp::gotMessage(ofMessage msg) {

}


void testApp::dragEvent(ofDragInfo dragInfo) {

}
