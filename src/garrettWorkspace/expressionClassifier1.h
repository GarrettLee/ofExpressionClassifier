#pragma once
#include "opencv2\opencv.hpp"
#include "svm.h"
#include "libSVMClassifier.h"
#include "expressionFeatureGetter.h"
#include "cvMatPlus.h"
namespace garrettWorkspace {
	class expressionClassifier1 {
	public:
		expressionClassifier1();
		expressionClassifier1(char * classifierModelDir, char *filterDir, char *baseDir);
		int classifyExpression(cv::Mat & src, cv::vector<ofVec2f> points, cv::vector<double> & probability);
		featureGetter featuregetter;

	private:
		pca pcaTool;
		cv::Mat filter;
		svmClassifier classifier;
		int posValueLength;
	};
}