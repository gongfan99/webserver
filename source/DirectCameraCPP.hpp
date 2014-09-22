#ifndef __DIRECTCAMERACPP_HPP__
#define __DIRECTCAMERACPP_HPP__

#include "SourceBase.hpp"

namespace ozo {

class DirectCameraCPP : public SourceBase{
public:
	DirectCameraCPP();
	~DirectCameraCPP();
	void process();
private:
	cv::Mat frame;
	cv::VideoCapture cap;
};

} //namespace ozo

#endif // __DIRECTCAMERACPP_HPP__