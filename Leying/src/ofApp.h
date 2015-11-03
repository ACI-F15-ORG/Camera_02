#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofTrueTypeFont font1, font2, font3;
    ofImage img, raw_img, mask, raw_mask;
    vector<ofImage> imgs, masks;
    int img_num = 0;
    int mask_num = 1;
    
    int threshold;
    float headposx, headposy, headposwidth, headposheight, oldheadposx, oldheadposy;
    
    ofVideoGrabber vidGrabber;
    ofxCvHaarFinder faceFinder;
    ofxCvColorImage	colorImg;
    
    bool begin = false;
    bool posvalid = false;
    
    float maxdist, d, r, g, b, adjustbrightness;
    int red, green, blue;
};
