#ifndef __ADAPTER_HPP__
#define __ADAPTER_HPP__

#include <cv.h>
#include <highgui.h>
#include "ImageProduce.h"

namespace ozo {

class Adapter {
public:
	ImageProduce* ImaPtr; //the external input interface
	IplImage* data; //the external output interface
	Adapter(ImageProduce* p) : ImaPtr(p) {}; //cast needed in the new statement
	~Adapter() {};
};

class AdapterDirect : public Adapter{
public:
	AdapterDirect(ImageProduce* p) : Adapter(p) {}; //cast needed in the new statement
	~AdapterDirect() {};
	
	void process() {
		data = ((ImageProduce*)ImaPtr)->data;
	}
};

} //namespace ozo

#endif // __ADAPTER_HPP__