#include "testApp.h"

//--------------------------------------------------------------
void setFloat3(float *f, ofPoint p) {
	f[0] = p.x;
	f[1] = p.y;
	f[2] = p.z;
}

void testApp::setup() {

	// setup kinect
//=============================================================================
	kinect.setRegistration(true);
	kinect.init();
	if (kinect.open()) {
		kinect_on = true;
	} else {
		kinect_on = false;
	}

	ofSetFrameRate(30);

	// setup UI
//=============================================================================
	grab_cam = new ofxGrabCam(false);
	grab_cam->reset();
	grab_cam->setPosition(1.0, 1.0, 1.0);
	grab_cam->lookAt(ofVec3f(0.0f, 0.0f, 0.0f));

	// setup data objects
//=============================================================================
	// CPU
	curr_f.init(DEPTH_X_RES, DEPTH_Y_RES);
	curr_f.allocateHost();
	// GPU
	curr_f.allocateDevice();

	min.set(-2.0, -2.0, -3.5);
	max.set(2.0, 2.0, -0.0);

	// GPU
	cudaMalloc((void **) &camera_opt.t, sizeof(float) * 16);
	cudaMalloc((void **) &camera_opt.it, sizeof(float) * 16);
	camera_opt.ref_pix_size = kinect.getRefPixelSize();
	camera_opt.ref_distance = kinect.getRefDistance();
	setFloat3(camera_opt.min, min);
	setFloat3(camera_opt.max, max);

	draw_normals = false;

	curr_f.host.step = 2;
	curr_f.dev.step = 2;
}

void testApp::exit() {

	delete grab_cam;

	curr_f.releaseHost();
	curr_f.releaseDevice();

	kinect.close();
}

void testApp::draw() {

	grab_cam->begin();

	if (kinect_on) {

		// only update the data if there is a new frame
		kinect.update();

		// there is a new frame
		if (kinect.isFrameNew()) {

			camera.setPosition(0.0f, 0.0f, 0.0f);
			camera.setOrientation(ofPoint(0.0f, 0.0f, 0.0f));
			curr_f.t = camera.getLocalTransformMatrix();
			curr_f.it = curr_f.t.getInverse();

			curr_f.setFromPixels(kinect.getDistancePixels());
			rangeToWorld(&camera_opt, &curr_f);

			curr_f.meshFromPoints(draw_normals, &kinect);
		}
	}

	curr_f.mesh.drawFaces();

	grab_cam->end();
}

void testApp::keyPressed(int key) {

	if (key == 'n') {
		draw_normals = !draw_normals;
	}
	if (key == OF_KEY_UP) {
		if (curr_f.host.step < 10) curr_f.host.step++;
		curr_f.dev.step = curr_f.host.step;
	}
	if (key == OF_KEY_DOWN) {
		if (curr_f.host.step > 1) curr_f.host.step--;
		curr_f.dev.step = curr_f.host.step;
	}
}

//--------------------------------------------------------------
void testApp::update() {
}
void testApp::keyReleased(int key) {
}
void testApp::mouseMoved(int x, int y) {
}
void testApp::mouseDragged(int x, int y, int button) {
}
void testApp::mousePressed(int x, int y, int button) {
}
void testApp::mouseReleased(int x, int y, int button) {
}
void testApp::windowResized(int w, int h) {
}
void testApp::gotMessage(ofMessage msg) {
}
void testApp::dragEvent(ofDragInfo dragInfo) {
}
