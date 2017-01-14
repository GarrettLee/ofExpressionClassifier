#include "cvMatPlus.h"

double matTypeTool::getDataAsDouble(cv::Mat mat, int x, int y, int c)
{
	int cvType = mat.type();
	int depth = CV_MAT_DEPTH(cvType);	//深度，也就是类型
	int channels = CV_MAT_CN(cvType);	//通道数
	int size = CV_ELEM_SIZE(cvType);
	double out;
	switch (depth) {
		//CV_8U
	case 0:
		
		out = *(unsigned char *)(mat.row(y).col(x).data + c *  size / channels);
		break;
		//CV_8S
	case 1:
		out = *(char *)(mat.row(y).col(x).data + c *  size / channels);
		break;
		//CV_16U
	case 2:
		out = *(unsigned short  *)(mat.row(y).col(x).data + c *  size / channels);
		break;
		
		//CV_16S
	case 3:
		out = *(short  *)(mat.row(y).col(x).data + c *  size / channels);
		break;
		
		//CV_32S
	case 4:
		out = *(int  *)(mat.row(y).col(x).data + c *  size / channels);
		break;
		
		//CV_32F
	case 5:
		out = *(float  *)(mat.row(y).col(x).data + c *  size / channels);
		break;
		
		//CV_64F
	case 6:
		out = *(double  *)(mat.row(y).col(x).data + c *  size / channels);
		break;
		
	default:
		break;
	}
	return out;
}

void matTypeTool::setDataAsDouble(cv::Mat mat, double in,  int x, int y, int c)
{
	int cvType = mat.type();
	int depth = CV_MAT_DEPTH(cvType);	//深度，也就是类型
	int channels = CV_MAT_CN(cvType);	//通道数
	int size = CV_ELEM_SIZE(cvType);
	switch (depth) {
		//CV_8U
	case 0:
	{
		unsigned char *ptr = mat.row(y).col(x).data + c *  size / channels;
		*ptr = in;
		break;
	}
		//CV_8S
	case 1:
	{
		char *ptr = (char *)(mat.row(y).col(x).data + c *  size / channels);
		*ptr = in;
		break;
	}
		//CV_16U
	case 2:
	{
		unsigned short *ptr = (unsigned short  *)(mat.row(y).col(x).data + c *  size / channels);
		*ptr = in;
		break;
	}
		//CV_16S
	case 3:
	{
		short *ptr = (short  *)(mat.row(y).col(x).data + c *  size / channels);
		*ptr = in;
		break;
	}
		//CV_32S
	case 4:
	{
		int *ptr = (int  *)(mat.row(y).col(x).data + c *  size / channels);
		*ptr = in;
		break;
	}
		//CV_32F
	case 5:
	{
		float *ptr = (float  *)(mat.row(y).col(x).data + c *  size / channels);
		*ptr = in;
		break;
	}
		//CV_64F
	case 6:
	{
		double *ptr = (double  *)(mat.row(y).col(x).data + c *  size / channels);
		*ptr = in;
		break;
	}
	default:
		break;
	}
}

//路径的分隔符可以是\\或者/
cv::Mat matIO::readMat(char * dir)
{
	cv::FileStorage fs = cv::FileStorage(dir, cv::FileStorage::READ);
	cv::Mat mat;
	fs["data"] >> mat;
	fs.release();
	return mat;
}
