#include "imageTool.h"
namespace garrettWorkspace {
	imageTool::imageTool() {

	}

	imageTool::imageTool(float height, float width) {
		this->height = height;
		this->width = width;
	}
	imageTool::imageTool(float height, float width, int channels) {
		this->channel = channels;
	}
	imageTool::~imageTool()
	{
	}

	
	

	
	//类lbpTool
	//lbpTool::lbpTool(float height, float width) :imageTool(height, width){}




	lbpTool::lbpTool()
	{
	}

	lbpTool::lbpTool(float height, float width, int rows, int cols, bool isVisuallize) : imageTool(height, width)
	{
		this->rows = rows;
		this->cols = cols;
		this->isVisuallize = isVisuallize;
		int bins[] = { 256 };
		float range[] = { 0, 255 };
		float* ranges[] = { range };
		this->hist = cvCreateHist(1, bins, CV_HIST_ARRAY, ranges, 1);
		this->lbpWindowHeight = height / rows;
		this->lbpWindowWidth = width / cols;
	}

	cv::Mat lbpTool::extractLbpFeature(cv::Mat & src, bool visuallize)
	{
		assert(src.type() == CV_8UC1);
		assert(src.rows == this->height);
		assert(src.cols == this->width);

		cv::Mat lbpHist(1, this->binNum * rows * cols, CV_32F);	//最终的lbp特征
		cv::MatIterator_<float> histPtr = lbpHist.begin<float>();		//迭代值

		cv::Mat dst(src.size(), src.type());
		lbp(src, dst);
		cv::Mat temp;
		for (int itx = 0; itx < cols; itx++) {
			for (int ity = 0; ity < rows; ity++) {
				dst(cv::Rect(itx * lbpWindowWidth, ity * lbpWindowHeight
					, lbpWindowWidth, lbpWindowHeight)).copyTo(temp);
				IplImage *lbp_map = &IplImage(temp);
				
				
				int bins[] = { 256 };
				float range[] = { 0, 255 };
				float* ranges[] = { range };
				CvHistogram * hist = cvCreateHist(1, bins, CV_HIST_ARRAY, ranges, 1);

				cvCalcHist(&lbp_map, hist, 0, 0);			//计算直方图
				cvNormalizeHist(hist, 1.0);					//直方图归一化
				for (int it = 0; it < 256; it++) {			//binNum为hist的bin的数目
					*histPtr = cvQueryHistValue_1D(hist, it);
					histPtr++;
				}
			}
		}
		if (visuallize) {
			dst.copyTo(src);
			for (int itx = 0; itx < cols; itx++) {
				for (int ity = 0; ity < rows; ity++) {
					cv::rectangle(src, cv::Rect(itx * lbpWindowWidth, ity * lbpWindowHeight
						, lbpWindowWidth, lbpWindowHeight), CV_RGB(0, 255, 0), 1);
				}
			}
		}
		return lbpHist;
	}

	cv::Mat lbpTool::extractLbpFeature(cv::Mat & src, cv::Mat & demo)
	{
		demo = src.clone();
		cv::Mat feature = extractLbpFeature(demo, true);
		return feature;
	}

	cv::Size lbpTool::getFeatureSize()
	{
		return cv::Size(1, this->binNum * rows * cols);
	}

	int lbpTool::getFeatureType()
	{
		return CV_32F;
	}

	

	void lbpTool::lbp(cv::Mat & src, cv::Mat & dst)
	{
		// 循环处理图像数据
		for (int i = 1; i < src.rows - 1; i++)
		{
			for (int j = 1; j < src.cols - 1; j++)
			{
				uchar tt = 0;
				int tt1 = 0;
				uchar u = src.at<uchar>(i, j);
				if (src.at<uchar>(i - 1, j - 1)>u) { tt += 1 << tt1; }
				tt1++;
				if (src.at<uchar>(i - 1, j)>u) { tt += 1 << tt1; }
				tt1++;
				if (src.at<uchar>(i - 1, j + 1)>u) { tt += 1 << tt1; }
				tt1++;
				if (src.at<uchar>(i, j + 1)>u) { tt += 1 << tt1; }
				tt1++;
				if (src.at<uchar>(i + 1, j + 1)>u) { tt += 1 << tt1; }
				tt1++;
				if (src.at<uchar>(i + 1, j)>u) { tt += 1 << tt1; }
				tt1++;
				if (src.at<uchar>(i + 1, j - 1)>u) { tt += 1 << tt1; }
				tt1++;
				if (src.at<uchar>(i - 1, j)>u) { tt += 1 << tt1; }
				tt1++;

				dst.at<uchar>(i - 1, j - 1) = tt;
			}
		}
	}
}