#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"


class ofApp : public ofBaseApp{
	
    public:
		
	void setup();
	void update();
	void draw();
    
    void mouseMoved(int x, int y);

    void audioOut(float * buffer, int bufferSize, int nChannels);
    
    //draw
    ofShader shader;
    ofPlanePrimitive plane,plane2,plane3;
    ofImage img;
    //audio
    maxiOsc osc,osc2,osc3;
    float bufferSize, sampleRate;
    float currentSample;
    float outputs[2];
    float lPos;
    float freq,freq2,freq3;
 
};
