#include "ofApp.h"
#include "fileLoaderThread.h"
#include "expressionThread.h"

using namespace ofxCv;
using namespace garrettWorkspace;
using namespace std;
lbpTool testLbpTool(720, 1280, 5, 5);
garrettWorkspace::expressionClassifier1 ec;
cv::vector<double> prob = {0,0,0,0,0,0, 0};
int expression;
string expressionName[] = { "anger", "contempt", "disgust", "fear", "happy", "sadness", "surprise" };
fileLoaderThread *flt;
struct dragMessage {
	string dragedImage;
	bool isDraged;
} ;
struct dragMessage dragedMessage = { string(), false };
void ofApp::setup() {
	fileLoaderThread::loaderSetting setting;
	setting.classifierModelDir = "data/classifier/model";
	setting.filterDir = "data/classifier/filter.xml";
	setting.baseDir = "data/classifier/base.xml";
	flt = new fileLoaderThread (&setting);
	flt->startThread(true, false);

	//while (flt->isThreadRunning());
	//ec =  garrettWorkspace::expressionClassifier1("data/classifier/model", "data/classifier/filter.xml", "data/classifier/base.xml");
	cam.initGrabber(640, 480);
	tracker.setup();
}

void ofApp::update() {

	cam.update();
	if(cam.isFrameNew() || dragedMessage.isDraged == true) {
		if (dragedMessage.isDraged == true) {
			try {
				pic.load(dragedMessage.dragedImage);
				if (!pic.isAllocated()) {
					exception e;
					throw e;
				}
			}
			catch (exception e) {
				frame = toCv(cam);
				dragedMessage.isDraged = false;
			}
			
			frame = toCv(pic);
		}
		else {
			frame = toCv(cam);
		}

		cv::GaussianBlur(frame, frame, cv::Size(5, 5), 0, 0);		//	È¥³ýÌõÎÆ
		if (frame.type() == CV_8UC3) {
			cv::cvtColor(frame, frame, CV_RGB2GRAY);
		}
		tracker.draw();
		bool featureTracked = tracker.update(frame);
		if (featureTracked) {
			if (!flt->isThreadRunning()) {
				ofVec3f test = tracker.getOrientation();
				float x = ofRadToDeg(test.x);
				float y = ofRadToDeg(test.y);
				float z = ofRadToDeg(test.z);
				if (abs(y) <10) {
					vector<ofVec2f> points = tracker.getImagePoints();
					flt->et->updata(frame, points);
					prob = flt->et->getProb();
					//ec.classifyExpression(frame, points, prob);
					expression = flt->et->getExpression();
				}
				else {
					expression = 0;

				}
			}
			
		}
		else {
			expression = 0;
		}
		
	}
}

void ofApp::draw() {
    ofSetColor(255);
	pic.setFromPixels((unsigned char *)IplImage(frame).imageData, frame.size().width, frame.size().height, OF_IMAGE_GRAYSCALE);
	pic.draw(0, 0);

	if (dragedMessage.isDraged == true) {
		ofDrawBitmapStringHighlight("Press backspace to resume!", 0, 200);
	}
    
	tracker.draw();
	//ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	if (expression != 0) {
		ofSetColor(ofColor::red);
		for (int i = 0; i < 7; i++) {
			float probI = SGN(prob[i] - 0.2);
			ofDrawRectangle(20 + i * 100 + (i - 1) * 10, (1 - probI) * 100, 80, 1 + 100 * (probI));
			ofDrawBitmapString(expressionName[i], 20 + i * 120, 120);
		}
	}
	else {
		ofSetColor(ofColor::gray);
		for (int i = 0; i < 7; i++) {
			float probI =0;
			ofDrawRectangle(20 + i * 100 + (i - 1) * 10, (1 - probI) * 100, 80, 1 + 100 * (probI));
			ofDrawBitmapString(expressionName[i], 20 + i * 120, 120);
		}
	}

}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
	if (key == OF_KEY_BACKSPACE) {
		dragedMessage.isDraged = false;
	}
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
	if (dragInfo.files.size() <= 1) {
		dragedMessage.dragedImage = dragInfo.files[0];
		dragedMessage.isDraged = true;
	}
	string fileDir = dragInfo.files[0];
}