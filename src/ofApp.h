#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "garrettWorkspace\imageTool.h"
#include "ofxFaceTracker.h"
#include "garrettWorkspace\expressionFeatureGetter.h"
#include "garrettWorkspace\expressionClassifier1.h"
#define SGN(x) x>0?x:0
class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ofImage pic;
	cv::Mat frame;


};
