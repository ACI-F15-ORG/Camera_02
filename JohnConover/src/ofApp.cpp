#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    kinect.setRegistration(true);
    // ofSetLogLevel(OF_LOG_VERBOSE);

    kinect.init();
    kinect.open();
    grayImg.allocate(kinect.width, kinect.height);
    colorImg.allocate(kinect.width, kinect.height);
    grayNear.allocate(kinect.width, kinect.height);
    grayFar.allocate(kinect.width, kinect.height);

    nearThreshold = 255;
    farThreshold = 150;

    ofEnableLighting();
    pointLight.setPointLight();
    // pointLight.setAttenuation(0.2);
    pointLight.setPosition(0,0,0);

    shiny.setSpecularColor(ofColor::gold);
    shiny.setDiffuseColor(ofColor::gold);
    shiny.setShininess(0.9);

    // point cloud resolution
    res = 4;
    capturing = true;
    wireframe = false;
    resChanged = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();

    if (kinect.isFrameNew() && capturing){
        grayImg.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
        grayNear = grayImg;
        grayFar = grayImg;
        grayNear.threshold(nearThreshold, true);
        grayFar.threshold(farThreshold);
        cvAnd(grayNear.getCvImage(), grayFar.getCvImage(), grayImg.getCvImage(), NULL);

        grayImg.flagImageChanged();

        conFinder.findContours(grayImg, 400, (kinect.width * kinect.height)/2, 3, false);

        meshes.clear();
        for (int i = 0; i < conFinder.nBlobs; i++){
            makeMesh(conFinder.blobs[i]);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //  grayImg.draw(0,0);
    //  conFinder.draw();
    // determine valid points in blob
    easyCam.begin();
    pointLight.enable();
    shiny.begin();

    // ofNoFill();
    ofPushMatrix();
    ofScale(1, -1, -1);
    ofTranslate(0, 0, -1000); // center the points a bit
    ofEnableDepthTest();

    for (int i = 0; i < meshes.size(); i++){
        if (wireframe){
            ofSetColor(ofColor::black);
            meshes[i].drawWireframe();
        }
        ofSetColor(ofColor::white);
        meshes[i].draw();
    }

    // triangulation.draw();
    ofDisableDepthTest();
    ofPopMatrix();

    // ofDrawSphere(pointLight.getPosition(), 10);
    shiny.end();
    pointLight.disable();
    easyCam.end();
}


void ofApp::makeMesh(const ofxCvBlob &blob){
    ofRectangle rect = blob.boundingRect;
    // ofMesh mesh;
    // mesh.setMode(OF_PRIMITIVE_POINTS);
    ofxDelaunay triangulation;
    for (int j = rect.y; j < rect.getMaxY(); j += res){
        for (int i = rect.x; i < rect.getMaxX(); i += res){
            ofColor c = grayImg.getPixelsRef().getColor(i, j);
            if (kinect.getDistanceAt(i, j) > 0 && c != ofColor::black){
                // mesh.addColor(kinect.getColorAt(i,j));
				// mesh.addVertex(kinect.getWorldCoordinateAt(i, j))
                triangulation.addPoint(kinect.getWorldCoordinateAt(i,j));
            }
        }
    }
    triangulation.triangulate();
    ofMesh mesh = triangulation.triangleMesh;
    vector<ofIndexType> indices = mesh.getIndices();
    for (int i = 0; i < indices.size(); i++){
        // ofVec2f point = vertices[i];
        // mesh.addColor(colorImg.getPixelsRef().getColor(point.x, point.y));
        // ofVec3f norm = mesh.getNormal(indices[i]);
        // mesh.setNormal(indices[i], norm);
    }
    // mesh.smoothNormals(10);

    meshes.push_back(mesh);

    triangulation.reset();
    // cout << "DRAWN" << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case ' ':
            capturing = !capturing;
            break;
        case 'w':
            wireframe = !wireframe;
            break;
        case OF_KEY_UP:
            res++;
            break;
        case OF_KEY_DOWN:
            if (res > 3){
                res--;
            }
            break;
        default:
            break;
    };
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    pointLight.setPosition(x-ofGetWidth()/2,-y+ofGetHeight()/2,-300);
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
