#include "expressionClassifier1.h"
using namespace garrettWorkspace;


/*
garrettWorkspace::expressionClassifier1::~expressionClassifier1()
{
}*/

garrettWorkspace::expressionClassifier1::expressionClassifier1()
{
}

garrettWorkspace::expressionClassifier1::expressionClassifier1(char * classifierModelDir, char * filterDir, char * baseDir)
{
	
	this->classifier = svmClassifier(classifierModelDir);
	this->filter = matIO::readMat(filterDir);
	this->pcaTool = pca(baseDir);
	assert(this->filter.rows == 1);

	cv::Mat temp = cv::Mat::ones(filter.cols, filter.rows, filter.type());
	
	this->posValueLength = matTypeTool::getDataAsDouble(this->filter * temp, 0, 0);
	assert(this->pcaTool.baseSize.width == this->classifier.getSampleLength());
	//assert(this->pcaTool.baseSize.height == this->posValueLength);
}

int expressionClassifier1::classifyExpression(cv::Mat & src, cv::vector<ofVec2f> points, cv::vector<double>& probability)
{
	cv::Mat feature = this->featuregetter.extractFeature(src, points);
	assert(feature.cols == this->filter.cols);
	cv::Mat filteredFeature(1, this->posValueLength, feature.type());
	int itF = 0;
	for (int i = 0; i < this->filter.cols; i++) {
		float v = matTypeTool::getDataAsDouble(this->filter, i, 0);
		
		if (v == 1) {
			matTypeTool::setDataAsDouble(filteredFeature, matTypeTool::getDataAsDouble(feature, i, 0), itF++, 0);
		}

	}

	
	assert(itF == this->posValueLength);
	cv::Mat pcaFeature = this->pcaTool.doPca(filteredFeature);
	

	return this->classifier.classify_probability(pcaFeature, probability);;
}
