#pragma once

#include "ofThread.h"
#include "garrettWorkspace\expressionClassifier1.h"
#include "opencv2\opencv.hpp"
template<class T> cv::vector<T> cloneVector(cv::vector<T> points) {
	cv::vector<T> temp;
	for (int i = 0; i < points.size(); i++) {
		temp.push_back(points[i]);
	}
	return temp;
}


class expressionThread : public ofThread {
public :
	expressionThread(char * classifierModelDir, char * filterDir, char * baseDir) {
		ec = garrettWorkspace::expressionClassifier1("data/classifier/model", "data/classifier/filter.xml", "data/classifier/base.xml");
		prob = { 0,0,0,0,0,0, 0 };
		expressionName = { "anger", "contempt", "disgust", "fear", "happy", "sadness", "surprise" };
		updatedFlag = false;
	}

	void threadedFunction() {
		while (isThreadRunning()) {
			
			if (updatedFlag) {
				lock();
				cv::Mat tempFrame = frame.clone();
				cv::vector<ofVec2f> tempPoints = cloneVector<ofVec2f>(points);
				unlock();
				cv::vector<double> tempProb;
				int tempExpression = ec.classifyExpression(tempFrame, tempPoints, tempProb);
				lock();
				this->prob = tempProb;
				this->expression = tempExpression;
				updatedFlag = false;
				unlock();
				
			}
		}
	}

	void updata(cv::Mat frame, cv::vector<ofVec2f> points) {
		lock();
		this->frame = frame;
		this->points = points;
		updatedFlag = true;
		unlock();
	}

	cv::vector<double> getProb() {

		lock();
		cv::vector<double> out = prob;
		//cv::vector<double> out = cloneVector<double>(prob);
		unlock();
		return out;
	}

	int getExpression() {
		lock();
		int temp = this->expression;
		unlock();
		return temp;
	}


	cv::vector<string> expressionName;
	
	
private:
	bool updatedFlag;
	cv::vector<double> prob;
	cv::Mat frame;
	cv::vector<ofVec2f> points;
	garrettWorkspace::expressionClassifier1 ec;
	int expression;
	


};


