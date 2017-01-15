#pragma once
#include "ofThread.h"
#include "expressionThread.h"

class fileLoaderThread : public ofThread {
public:
	struct loaderSetting {
		char * classifierModelDir;
		char * filterDir;
		char * baseDir;
	}  typedef  loaderSetting;
	fileLoaderThread(loaderSetting * setting):ofThread(){
		this->setting = *setting;
	}
	~fileLoaderThread() {
		this->stopThread();
		if (et != nullptr) {
			et->stopThread();
			delete et;
		}
	}
	void threadedFunction() {
		lock();
		et = new expressionThread(setting.classifierModelDir, setting.filterDir, setting.baseDir);
		et->startThread(true, false);
		unlock();
	}
	expressionThread *et = nullptr;
	loaderSetting setting;
};
