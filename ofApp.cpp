#include "ofApp.h"

using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(false);
	ofSetFrameRate(CAMERA_FRAMERATE);

	pgr_camera = new ofxFlyCap2();
	pgr_camera->setup(0, 0, CAMERA_W, CAMERA_H, FlyCapture2::MODE_0, FlyCapture2::PIXEL_FORMAT_RAW8); //PIXEL_FORMAT_RAW8, PIXEL_FORMAT_MONO8

	float fps = CAMERA_FRAMERATE;
	pgr_camera->setShutterSpeed(1000 / fps);
	pgr_camera->setFrameRate(fps);

	// init cv variables
	src_img = Mat(CAMERA_W, CAMERA_H, CV_8UC1);
	bg_img = Mat(CAMERA_W, CAMERA_H, CV_8UC1);
	diff_img = Mat(CAMERA_W, CAMERA_H, CV_8UC1);
	dest_img = Mat(CAMERA_W, CAMERA_H, CV_8UC3);
	grabBG = false;

	showGui = true;


	// spout settings
	sender.init("shadow");
}

//--------------------------------------------------------------
void ofApp::update(){

	pgr_camera->grab_image();

	// copy src image
	src_img = pgr_camera->getImageMat();

	// grab background image
	if (grabBG)
	{
		bg_img = src_img.clone();
		grabBG = false;
	}

	// subtraction
	diff_img = -src_img + bg_img;

	// convert to color image
	// maybe spout accept only color image
	cvtColor(diff_img, dest_img, CV_GRAY2BGR);

	// convert to ofImage
	bgImage.setFromPixels(bg_img.data, CAMERA_W, CAMERA_H, OF_IMAGE_GRAYSCALE);
	bgImage.update();
	diffImage.setFromPixels(diff_img.data, CAMERA_W, CAMERA_H, OF_IMAGE_GRAYSCALE);
	diffImage.update();
	destImage.setFromPixels(dest_img.data, CAMERA_W, CAMERA_H, OF_IMAGE_COLOR);
	destImage.update();

	sender.send(destImage.getTexture());
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);

	ofImage img = pgr_camera->getOfImage();
	img.draw(0, 0, CAMERA_W / 2, CAMERA_H / 2);
	destImage.draw(0, CAMERA_H / 2, CAMERA_W / 2, CAMERA_H / 2);
	bgImage.draw(CAMERA_W / 2, 0, CAMERA_W / 2, CAMERA_H / 2);

	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 10, 15);
}

//--------------------------------------------------------------
void ofApp::exit() {

	delete pgr_camera;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key)
	{
	case 'b':
		grabBG = !grabBG;
		break;

	case 'f':
		ofToggleFullscreen();
		break;

	case 'g':
		showGui = !showGui;
		break;

	default:
		break;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
