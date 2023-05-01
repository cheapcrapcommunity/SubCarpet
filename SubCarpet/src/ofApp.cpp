#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

//-------------------
    //load shaders
#ifdef TARGET_OPENGLES
	shader.load("shadersES2/shader");
#else
	if(ofIsGLProgrammableRenderer()){
		shader.load("shadersGL3/shader");
	}else{
		shader.load("shadersGL2/shader");
	}
#endif
    
    //set img
    img.allocate(80, 60, OF_IMAGE_GRAYSCALE);
    //set plane
    plane.set(800, 600, 80, 60);
    plane2.set(800, 400, 80, 60);
    plane3.set(800, 200, 80, 60);
    plane.mapTexCoordsFromTexture(img.getTexture());
    plane2.mapTexCoordsFromTexture(img.getTexture());
    plane3.mapTexCoordsFromTexture(img.getTexture());
    //setting for dsp
    sampleRate = 44100;
    bufferSize = 512;
    //initiallize frequency
    freq=0;
    freq2=0;
    freq3=0;
    
    ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //define noise
    float noiseScale;
    if(mouseX<=ofGetWidth()/2){
        noiseScale = (double)ofMap(mouseX, 0, ofGetWidth()/2, 0, 0.05);
    }else{
        noiseScale = (double)ofMap(mouseX, ofGetWidth()/2, ofGetWidth(), 0.05, 0);
    }
    
    float noiseVel = ofGetElapsedTimef();
    //cout<<noiseVel<<endl;
    
    ofPixels & pixels = img.getPixels();
    
    int w = img.getWidth();
    int h = img.getHeight();
    
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            int i = y * w + x;
            float noiseVelue = ofNoise(x * noiseScale, y * noiseScale, noiseVel);
            //cout<<noiseVelue<<endl;
            pixels[i] = 255 * noiseVelue;
            //map frequency with pixels
            freq = pixels[i]/3;
            freq2 = pixels[i]/2;
            freq3 = pixels[i];
            //cout<<freq3<<endl;
        }
    }
    img.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    // bind texture in shader
    
    img.getTexture().bind();

    shader.begin();

    ofPushMatrix();

    // translate plane into center
    float tx = ofGetWidth() / 2;
    float ty = ofGetHeight() / 2;
    ofTranslate(tx, ty);

    // the mouseY position changes the rotation
    float percentY = mouseY / (float)ofGetHeight();
    float rotation = ofMap(percentY, 0, 1, -60, 300, true) + 60;
    
    ofRotateDeg(rotation, 1, 0, 0);

    plane.drawWireframe();
    plane2.drawWireframe();
    plane3.drawWireframe();
    
    ofPopMatrix();

    shader.end();

    ofSetColor(ofColor::white);
    img.draw(0, 0);
    
    //ofBackgroundGradient(ofColor(60,60,60,20), ofColor(10,10,10,20));


}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    lPos = (double)ofMap(x, 0, ofGetWidth(), 0, 1.0);
}



void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    
    for(unsigned i = 0; i < bufferSize; i++){
        //fm synthesize
        currentSample = osc.sinewave(freq*osc2.sinewave(freq2*osc3.sinewave(freq3)));
        
        output[i * nChannels] =  currentSample * (1-lPos);
        output[i * nChannels + 1] =  currentSample * lPos;

    }
}
