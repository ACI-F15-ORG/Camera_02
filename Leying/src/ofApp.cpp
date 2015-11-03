#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    raw_mask.loadImage("mask1.jpg");
    masks.push_back(raw_mask);
    raw_mask.loadImage("mask2.jpg");
    masks.push_back(raw_mask);
    raw_mask.loadImage("mask3.jpg");
    masks.push_back(raw_mask);
    
    raw_img.loadImage("BoutonRd.jpg");
    imgs.push_back(raw_img);
    raw_img.loadImage("Maple.jpg");
    imgs.push_back(raw_img);
    raw_img.loadImage("Troy.jpg");
    imgs.push_back(raw_img);
    raw_img.loadImage("VCC.jpg");
    imgs.push_back(raw_img);
    raw_img.loadImage("union.jpg");
    imgs.push_back(raw_img);
    raw_img.loadImage("bridge.jpg");
    imgs.push_back(raw_img);
    raw_img.loadImage("academy.jpg");
    imgs.push_back(raw_img);
    raw_img.loadImage("bio.jpg");
    imgs.push_back(raw_img);
    threshold = 160;
    
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320, 200);
    
    faceFinder.setup("haarcascade_frontalface_default.xml");
    
    font1.loadFont("AmericanTypewriter.ttc", 30);
    font2.loadFont("AmericanTypewriter.ttc", 40);
    font3.loadFont("AmericanTypewriter.ttc", 10);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    img = imgs[img_num];
    mask = masks[mask_num];
    
    vidGrabber.update();
    if (vidGrabber.isFrameNew()) {
        faceFinder.findHaarObjects(vidGrabber.getPixelsRef());
    }
    
    //Find face position
    headposx = headposy = headposwidth = headposheight = 0;
    for (int i = 0; i < faceFinder.blobs.size(); i++) {
         if (headposwidth*headposheight <
             faceFinder.blobs[i].boundingRect.width*faceFinder.blobs[i].boundingRect.height){
             headposwidth = faceFinder.blobs[i].boundingRect.width;
             headposheight = faceFinder.blobs[i].boundingRect.height;
             headposx = (240 - faceFinder.blobs[i].boundingRect.x)*6;
             headposy = (faceFinder.blobs[i].boundingRect.y+20)*6;
         }
    }
    
    //Check whether values stored in headposx and headposy
    //also limit the changes of the postions
    if (headposx>0 && headposy>0){
        posvalid = true;
        if (oldheadposx>0 && oldheadposy>0){
            if (headposx - oldheadposx > 40){
                headposx = oldheadposx + 40;
            }
            if (headposy - oldheadposy > 40){
                headposy = oldheadposy + 40;
            }
            if (oldheadposx - headposx > 40){
                headposx = oldheadposx - 40;
            }
            if (oldheadposy - headposy > 40){
                headposy = oldheadposy - 40;
            }
        }
    }
    else{
        posvalid = false;
    }
    
    img.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    img.draw(0, 0);
    //Relocate the face location if the new location is not far away from
    //the previous face location
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    if ((!begin || posvalid)) {
        
        begin = true;
        ofSetRectMode(OF_RECTMODE_CENTER);
        masks[mask_num].draw(headposx, headposy);
        ofSetRectMode(OF_RECTMODE_CORNER);
        
        oldheadposx = headposx;
        oldheadposy = headposy;
    }
    //Repeat previous action otherwise
    else{
        
        //Draw if values in oldheadposx and oldheadposy
        if (oldheadposx>0 && oldheadposy>0){
            ofSetRectMode(OF_RECTMODE_CENTER);
            masks[mask_num].draw(oldheadposx, oldheadposy);
            ofSetRectMode(OF_RECTMODE_CORNER);
        }
    }
    ofDisableBlendMode();
    font1.drawString("Press UP or DOWN to switch slits.", 40, 910);
    font1.drawString("Press LEFT or RIGHT to switch pictures.", 40, 880);
    font2.drawString("Camera", 40, 770);
    font2.drawString("Leying Hu", 40, 820);
    font2.drawString("__________", 40, 840);
    font3.drawString("Photos credit to Xi Wang and Tonghe Zhang.", 40, 930);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 356){
        if (img_num==0) img_num = 7;
        else img_num--;
    }
    if (key == 358){
        if (img_num==7) img_num = 0;
        else img_num++;
    }
    if (key == 357){
        if (mask_num==2) mask_num = 0;
        else mask_num++;
    }
    if (key == 359){
        if (mask_num == 0) mask_num = 2;
        else mask_num--;
    }
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
