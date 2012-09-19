#pragma once

#include "ofMain.h"

#include "ofxKinect.h"
#include "ofxGrabCam.h"
#include "ofxRangeToWorldCUDA.h"

#include <cutil_inline.h>    // includes cuda.h and cuda_runtime_api.h
#define DEPTH_X_RES 640
#define DEPTH_Y_RES 480

class testApp: public ofBaseApp {

	ofxKinect kinect;
	bool kinect_on;

	// thresholds for the depth data
	// use only the points inside of the 3d box
	ofPoint min;
	ofPoint max;

	// camera used for mesh viewing
	ofxGrabCam *grab_cam;

	// camera used to model kinect position
	// in the world coordinates
	ofCamera camera;

	Frame curr_f; // in first prototype, just a snapshot
	CameraOptions camera_opt;

	bool draw_normals;

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
