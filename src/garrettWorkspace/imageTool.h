#pragma once
#include<opencv2\opencv.hpp>
#include<opencv\cv.h>
namespace garrettWorkspace {
	class imageTool{
	public:
		imageTool();
		imageTool(float height, float width);
		imageTool(float height, float width, int channel);
		~imageTool();

	protected:
		float height = 0;
		float width = 0;
		int channel = 1;
	};


	class lbpTool :  imageTool {
	public:
		lbpTool();
		lbpTool(float height, float width, int rows, int cols, bool isVisuallize = false);
		cv::Mat extractLbpFeature(cv::Mat & src, bool visuallize = false);
		cv::Mat extractLbpFeature(cv::Mat & src, cv::Mat & demo);
		cv::Size getFeatureSize();
		int getFeatureType();
		static void lbp(cv::Mat & src, cv::Mat & dst);
	private:
		
		int rows = 1;
		int cols = 1;
		int lbpWindowHeight = 0;
		int lbpWindowWidth = 0;
		bool isVisuallize = false;
		int channel = 1;
		CvHistogram * hist;
		int binNum = 256;
	};
}