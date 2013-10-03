#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
    bool antiAlias=true;
    bool fullScreen=true;
	ofAppGlutWindow window;
    if (antiAlias) window.setGlutDisplayString("rgb alpha double samples depth"); //rgb double depth alpha samples>=4
    if (fullScreen) ofSetupOpenGL(&window, 1024, 768, OF_FULLSCREEN);
    else ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
}
