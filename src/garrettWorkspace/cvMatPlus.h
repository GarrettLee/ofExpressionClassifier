#pragma once
#include "opencv2\opencv.hpp"

//���ļ����д���Ϊ�˷��㵫��Ч�ʵ͵ķ�����ֻΪ�˷����ʹ��

//ͬһʹ��double�Ծ�����ж�д������ע����ܻ�Ӱ��Ч�ʡ������ڲ��Ե�ʱ��ʹ�ã���������ֱ����opencv�Դ��ķ�����д��
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