#ifndef __SOURCEBASE_HPP__
#define __SOURCEBASE_HPP__

#include <cv.h>
#include <highgui.h>
#include "ImageProduce.h"

namespace ozo {

class SourceBase {
public:
	cv::Mat *data; //the external output interface
	SourceBase() {};
	~SourceBase() {};
};

class DirectCamera : public SourceBase{
public:
	Adapter
	DirectCamera() {};
	~DirectCamera() {};
	
	void process() {
		data = ((ImageProduce*)ImaPtr)->data;
	}
};

} //namespace ozo

#endif // __SOURCEBASE_HPP__