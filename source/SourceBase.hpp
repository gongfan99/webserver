#ifndef __SOURCEBASE_HPP__
#define __SOURCEBASE_HPP__

#include <cv.h>
#include <highgui.h>

namespace ozo {

class SourceBase {
public:
	cv::Mat data; //the external output interface
	SourceBase() {};
	~SourceBase() {};
};

} //namespace ozo

#endif // __SOURCEBASE_HPP__