#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofEvents.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        ofImage diagram;
        ofTrueTypeFont		font;

		ofVideoGrabber vidGrabber;
		ofxCvContourFinder contourFinder;

		ofxCvGrayscaleImage grayImg;
		ofxCvColorImage colorImg;


		int vidWidth;
		int vidHeight;

		ofxKinect kinect;
		ofxCvGrayscaleImage grayThreshNear;
		ofxCvGrayscaleImage grayThreshFar;

		bool bThreshWithOpenCV;

		int nearThreshold;
		int farThreshold;

        vector<float> storeBlobs;
        vector<ofPoint> storeCentroid;


        float largest;
        float largeCenterx;
        float largeCentery;

        ofArduino	ard;
        bool		bSetupArduino;

private:

    void setupArduino(const int & version);
	void updateArduino();

};


