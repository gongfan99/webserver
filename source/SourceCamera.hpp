#ifndef __OZO_SOURCECAMERA_HPP__
#define __OZO_SOURCECAMERA_HPP__

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

#endif // __OZO_SOURCECAMERA_HPP__