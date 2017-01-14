#include "expressionFeatureGetter.h"
featureGetter::featureGetter()
{
	this->lbpT = garrettWorkspace::lbpTool(patchSize[0], patchSize[1], lbpBlockNum[0], lbpBlockNum[1]);
}

cv::Mat featureGetter::extractFeature(cv::Mat & src, vector<ofVec2f> points)
{
	cv::Mat cliped = clipAndRescale(src, points);
	cv::MatIterator_<float> itx = keysx.begin<float>();
	cv::MatIterator_<float> ity = keysy.begin<float>();
	
 	float marginY = patchSize[0] / 2;
	float marginX = patchSize[1] / 2;

	cv::Mat feature = cv::Mat(cv::Size(lbpT.getFeatureSize().height * keysx.cols, 1), lbpT.getFeatureType());
	int featureIt = 0;
	for (int i = 0; i < keysx.cols; i++) {
		//cv::circle(cliped, cv::Point(*itx++, *ity++), 3, CV_RGB(0, 255, 0), 1, 8, 3);
		cv::Mat patch = cliped(cv::Rect((*itx++ - marginX), (*ity++ - marginY), patchSize[1], patchSize[0]));
		lbpT.extractLbpFeature(patch, true).copyTo(feature(cv::Rect(featureIt, 0, lbpT.getFeatureSize().height, 1)));
		featureIt += lbpT.getFeatureSize().height;

	}
	
	return feature;
}

cv::Mat featureGetter::clipAndRescale(cv::Mat src, vector<ofVec2f> points)
{
	ofVec2f minxy, maxxy;
	getBoundance(points, minxy, maxxy);


	//这里是错的！！！但是因为训练的分类器是基于这个错的剪裁方法的样本训练出来的，所以这里要将错就错
	h = round((maxxy[1] - minxy[1]) * (1 + this->clipMargin));
	w = round((maxxy[0] - minxy[0]) * (1 + this->clipMargin));
	xs = round((minxy[0] + maxxy[0]) / 2 - w / 2);
	ys = round((minxy[1] + maxxy[1]) / 2 - h / 2);
	ys = ys > 0 ? ys : 0;
	xs = xs > 0 ? xs : 0;
	w = w + xs + 1 > src.cols ? src.cols - xs - 1: w;
	h = h + ys + 1 > src.rows ? src.rows - ys - 1: h;
	cv::Mat cliped = src(cv::Rect(xs, ys, w, h));
	float scale = (double)desireWidth / (double)w;
	cv::Size newSize(desireWidth, scale * h);
	cv::resize(cliped, cliped, newSize);

	keys = getKeypoint(points);
	keysx = cv::Mat(1, keys.cols / 2, keys.type());
	keysy = cv::Mat(1, keys.cols / 2, keys.type());

	keysx
		= (keys(cv::Rect(0, 0, keys.cols / 2,1)) - xs) * scale;
	keysy
		= (keys(cv::Rect(keys.cols /2, 0, keys.cols / 2, 1)) - ys) * scale;
	


	return cliped;
}

void featureGetter::getBoundance(vector<ofVec2f> points, ofVec2f & minxy, ofVec2f & maxxy)
{
	minxy[0] = points[0][0];	//x
	minxy[1] = points[0][1];	//y
	maxxy[0] = 0;	//x
	maxxy[1] = 0;	//y
	for (int i = 0; i < points.size(); i++) {
		if (points[i][0] < minxy[0]) {
			minxy[0] = points[i][0];
		}
		else if (points[i][0] > maxxy[0]) {
			maxxy[0] = points[i][0];
		}

		if (points[i][1] < minxy[1]) {
			minxy[1] = points[i][1];
		}
		else if (points[i][1] > maxxy[1]) {
			maxxy[1] = points[i][1];
		}
	}
}


cv::Mat featureGetter::getKeypoint(vector<ofVec2f> points)
{
	cv::Mat out(1, keypoints.size() * 2, CV_32FC1);
	cv::MatIterator_<float> xit = out.begin<float>();
	cv::MatIterator_<float> yit = xit + keypoints.size();
	for (int i = 0; i < keypoints.size(); i++) {
		*xit++ = points[keypoints[i]][0];
		*yit++ = points[keypoints[i]][1];
	}
	return out;
}
