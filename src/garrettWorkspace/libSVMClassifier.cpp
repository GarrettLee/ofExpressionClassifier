#include "libSVMClassifier.h"

svmClassifier::svmClassifier()
{
}

svmClassifier::svmClassifier(char * dir)
{
	this->model = svm_load_model(dir);
	svm_node * p = this->model->SV[0];
	for ( ; p->index != -1; p++);
	this->sampleLength = (--p)->index;
	this->classNum = this->model->nr_class;
	for (int i = 0; i < this->classNum; i++) {
		this->labels.push_back(this->model->label[i]);
	}
}

int svmClassifier::classify(cv::Mat feature)
{
	assert(feature.cols == this->sampleLength && feature.rows == 1 && feature.channels() == 1);
	struct svm_node* x = (struct svm_node*)malloc(this->sampleLength * sizeof(struct svm_node));
	cv2nodes(feature,x);
	int c = svm_predict(model, x);
	free(x);
	return c;
}

//probability中各类的顺序和成员变量labels的排序一致
int svmClassifier::classify_probability(cv::Mat feature, cv::vector<double>& probability)
{
	assert(feature.cols == this->sampleLength && feature.rows == 1 && feature.channels() == 1);
	struct svm_node* x = (struct svm_node*)malloc((this->sampleLength + 1 )* sizeof(struct svm_node));
	cv2nodes(feature,x);
	double * prob = (double *)malloc((this->classNum ) * sizeof(double));
	struct svm_node* p = x;
	int c = svm_predict_probability(model, p, prob);
	free(x);
	probability.clear();
	for (int i = 0; i < this->classNum; i++) {
		probability.push_back(prob[i]);
	}
	free(prob);
	return c;
}

int svmClassifier::getSampleLength()
{
	return this->sampleLength;
}

void svmClassifier::cv2nodes(cv::Mat sample, struct svm_node* x)
{
	
	for (int i = 0; i < sample.cols; i++) {
		x[i].index = i + 1;
		x[i].value = matTypeTool::getDataAsDouble(sample, i, 0);
	}
	x[sample.cols].index = -1;
	return;
}



pca::pca()
{
}

pca::pca(char * dir)
{
	this->base = matIO::readMat(dir);
	this->baseSize = this->base.size();
	
}

cv::Mat pca::doPca(cv::Mat sample)
{
	cv::Mat out;
	assert(sample.cols == this->base.rows);
	out = sample * this->base;
	return out;
}
