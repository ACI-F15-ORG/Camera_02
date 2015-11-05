#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);

	ofSetLogLevel(OF_LOG_VERBOSE);

	kinect.setRegistration(true);

	kinect.init();

	kinect.open();		// opens first available kinect

	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
}

    colorImg.allocate(kinect.width, kinect.height);
    grayImg.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);

	nearThreshold = 255;
	farThreshold = 200;
	bThreshWithOpenCV = true;  //changing thresh? dont need....

	ard.connect("/dev/ttyUSB0", 57600);
	ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
	bSetupArduino	= false;
	//Remember on Arduino side it is a nano

    diagram.loadImage("TheLookOut.jpg");
    diagram.resize(ofGetWidth(), ofGetHeight());

    font.loadFont("franklinGothic.otf", 20);

}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();
	updateArduino();

	if(kinect.isFrameNew())
{

    grayImg.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
	unsigned char * pix = grayImg.getPixels();

			int numPixels = grayImg.getWidth() * grayImg.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] < nearThreshold && pix[i] > farThreshold) {
					pix[i] = 255;
				} else {
					pix[i] = 0;
				}
			}
        grayImg.flagImageChanged();
		contourFinder.findContours(grayImg, 100, (kinect.width*kinect.height)/2, 5, false);
    largest = 0;
    for(int i=0; i<contourFinder.nBlobs; i++){

        if(contourFinder.blobs[i].boundingRect.width > largest){
            largest = contourFinder.blobs[i].boundingRect.width/2;
            largeCenterx = contourFinder.blobs[i].centroid.x;
            largeCentery = contourFinder.blobs[i].centroid.y;
        }
}

       if((largeCenterx > 0) && (largeCenterx < kinect.width*1/3)){

        cout << "zone1" << endl;
        ard.sendDigital(4, ARD_HIGH);
        ard.sendDigital(6, ARD_LOW);
        ard.sendDigital(8, ARD_LOW);
        //zone 1 vibrate
       }
       if((largeCenterx >= kinect.width*1/3) && (largeCenterx <= kinect.width*2/3)){

        cout << "zone2" << endl;
        ard.sendDigital(6, ARD_HIGH);
        ard.sendDigital(4, ARD_LOW);
        ard.sendDigital(8, ARD_LOW);
        //zone 2 vibrate
       }
       if((largeCenterx > kinect.width*2/3) && (largeCenterx < kinect.width)){

        cout << "zone3" << endl;
        ard.sendDigital(8, ARD_HIGH);
        ard.sendDigital(4, ARD_LOW);
        ard.sendDigital(6, ARD_LOW);
        //zone 3 vibrate
       }

        if(largest<=10){
        ard.sendDigital(8, ARD_LOW);
        ard.sendDigital(4, ARD_LOW);
        ard.sendDigital(6, ARD_LOW);

        }

}
}

void ofApp::setupArduino(const int & version) {


	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);

    bSetupArduino = true;

    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();


    ard.sendDigitalPinMode(4, ARD_OUTPUT);  //zone1 motor
    ard.sendDigitalPinMode(6, ARD_OUTPUT);  //zone 2 motor
    ard.sendDigitalPinMode(8, ARD_OUTPUT);  // zone 3 motor


}

//--------------------------------------------------------------
void ofApp::updateArduino(){

	ard.update();
}
//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(ofColor::white);
	grayImg.draw(0,0);
    diagram.draw(0, 0);


	ofSetColor(ofColor::blue);

    contourFinder.draw(0, 0, kinect.width, kinect.height);

    ofFill();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofCircle(largeCenterx, largeCentery, largest);
    ofSetRectMode(OF_RECTMODE_CORNER);

    ofNoFill();
    ofLine(kinect.width*1/3, 0, kinect.width*1/3, kinect.height);
    ofLine(kinect.width*2/3, 0, kinect.width*2/3, kinect.height);
    ofLine(0, kinect.height/2, kinect.width, kinect.height/2);

    font.drawString("Zone 1\n", 15, kinect.height);
    font.drawString("Zone 2\n", kinect.width*1/3 +15, kinect.height);
    font.drawString("Zone 3\n", kinect.width*2/3 +15, kinect.height);
	}



