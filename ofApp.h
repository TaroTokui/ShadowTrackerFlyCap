#pragma once

#include "ofMain.h"
#include "ofxFlyCap2.h"
#include "ofxGui.h"
#include "ofxSpout.h"
#include "ofxBezierWarpManager.h"

static const int CAMERA_W = 1280; 
static const int CAMERA_H = 720;
static const int CAMERA_FRAMERATE = 60;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
private:
	ofxFlyCap2 *pgr_camera;

	// cv variables
	cv::Mat src_img;
	cv::Mat bg_img;
	cv::Mat diff_img; 
	cv::Mat dest_img;
	bool grabBG;

	// GUI variables
	ofxPanel gui;
	ofParameterGroup gui_params;
	ofParameter<int> binarize_threshold;
	bool showGui;

	// ofImage
	ofImage diffImage;
	ofImage bgImage;
	ofImage destImage;

	// spout
	ofxSpout::Sender sender;

	// mapper
	ofxBezierWarpManager bezManager;
	ofFbo camera_fbo;
	ofFbo spout_fbo;
};
