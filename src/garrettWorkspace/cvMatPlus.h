#pragma once
#include "opencv2\opencv.hpp"

//此文件下有大量为了方便但是效率低的方法，只为了方便而使用

//同一使用double对矩阵进行读写，但是注意可能会影响效率。可以在测试的时候使用，但最后最好直接用opencv自带的方法读写。
class matTypeTool {
public:
	static double getDataAsDouble(cv::Mat mat, int x, int y, int c = 0);
	static void setDataAsDouble(cv::Mat mat, double in,  int x, int y, int c = 0);
private:
	
};

class matIO {
public:
	static cv::Mat readMat(char * dir);
};