#pragma once
#include<opencv2\opencv.hpp>
#include "svm.h"
#include "cvMatPlus.h"
class svmClassifier {
public:
	svmClassifier();
	svmClassifier(char * dir);
	int classify(cv::Mat feature);
	int classify_probability(cv::Mat feature, cv::vector<double> & probability);
	int getSampleLength();
private:
	void cv2nodes(cv::Mat sample, struct svm_node *x);
	cv::vector<double> labels;
	int classNum;
	int sampleLength;
	struct svm_model *model;
};

class pca
{
public:
	pca();
	pca(char * dir);
	cv::Mat doPca(cv::Mat sample);
	cv::Size baseSize;

private:
	cv::Mat base;
};