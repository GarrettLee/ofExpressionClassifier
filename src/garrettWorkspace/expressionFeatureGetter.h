#pragma once
#include "ofMain.h"
#include "ofxCv.h"
#include "garrettWorkspace\imageTool.h"

class featureGetter {
public:
	featureGetter();
	cv::Mat extractFeature(cv::Mat & src, vector<ofVec2f> points);
	cv::Mat clipAndRescale(cv::Mat src, vector<ofVec2f> points);

private:
	cv::vector<int> keypoints = { 54, 48, 27, 31, 35, 21, 22, 36, 45 };
	ofVec2f lbpBlockNum = {5,5};
	ofVec2f patchSize = { 50, 50 };			//第一个元素是高，第二个是宽
	float desireWidth = 348.669;
	float clipMargin = 0.2;				//剪裁人脸时多剪出来的边缘

	
	void getBoundance(vector<ofVec2f> points, ofVec2f & minxy, ofVec2f & maxxy);
	cv::Mat getKeypoint(vector<ofVec2f> points);

	int xs = 0;
	int ys = 0;
	int w = 0;
	int h = 0;

	cv::Mat keys;
	cv::Mat keysx;
	cv::Mat keysy;

	garrettWorkspace::lbpTool lbpT ;


};