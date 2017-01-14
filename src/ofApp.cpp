#include "ofApp.h"
using namespace ofxCv;
using namespace garrettWorkspace;
using namespace std;
lbpTool testLbpTool(720, 1280, 5, 5);
garrettWorkspace::expressionClassifier1 ec;
cv::vector<double> prob = {0,0,0,0,0,0, 0};
int expression;
string expressionName[] = { "anger", "contempt", "disgust", "fear", "happy", "sadness", "surprise" };

void ofApp::setup() {
	ec =  garrettWorkspace::expressionClassifier1("data/classifier/model", "data/classifier/filter.xml", "data/classifier/base.xml");

	cam.initGrabber(640, 480);
	tracker.setup();

	

}

void ofApp::update() {
	
	cam.update();
	if(cam.isFrameNew()) {
		//pic.load("face.png");
		//frame = toCv(pic);
		frame = toCv(cam);
		cv::GaussianBlur(frame, frame, cv::Size(5, 5), 0, 0);		//	È¥³ýÌõÎÆ
		if (frame.type() == CV_8UC3) {
			cv::cvtColor(frame, frame, CV_RGB2GRAY);
		}
		bool featureTracked = tracker.update(frame);
		if (featureTracked) {
			vector<ofVec2f> points = tracker.getImagePoints();
			
			expression = ec.classifyExpression(frame, points, prob);
		}
		
	}
}

void ofApp::draw() {
    ofSetColor(255);
	pic.setFromPixels((unsigned char *)IplImage(frame).imageData, frame.size().width, frame.size().height, OF_IMAGE_GRAYSCALE);
	pic.draw(0, 120);

    ofSetColor(ofColor::red);

	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	for (int i = 0; i < 7; i++) {
		float probI = SGN(prob[i] - 0.4);
		ofDrawRectangle(20 + i * 100 + (i - 1) * 10, (1 - probI) * 100, 80, 1 + 100 * (probI));
		ofDrawBitmapString(expressionName[i], 20 + i * 120, 120);
	}
	

}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}
