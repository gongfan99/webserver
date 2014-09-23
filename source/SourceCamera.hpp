#ifndef __SOURCECAMERA_HPP__
#define __SOURCECAMERA_HPP__

#include <cv.h>
#include <highgui.h>

namespace ozo {

class SourceCamera {
public:
	cv::Mat data; //the external output interface
	SourceCamera();
	~SourceCamera();
	void process();
private:
	cv::Mat frame;
	cv::VideoCapture cap;
};

} //namespace ozo

#endif // __SOURCECAMERA_HPP__