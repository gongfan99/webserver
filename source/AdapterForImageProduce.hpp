#ifndef __ADAPTERFORIMAGEPRODUCE_HPP__
#define __ADAPTERFORIMAGEPRODUCE_HPP__

#include <cv.h>
#include <highgui.h>
#include "ImageProduce.h"

class AdapterForImageProduce {
public:
	ImageProduce* ImaPtr; //the external input interface
	IplImage* data; //the external output interface
	AdapterForImageProduce(ImageProduce* p) : ImaPtr(p) {}; //cast needed in the new statement
	~AdapterForImageProduce() {};
};

class AdapterForImageProduceDirect : public AdapterForImageProduce{
public:
	AdapterForImageProduceDirect(ImageProduce* p) : AdapterForImageProduce(p) {}; //cast needed in the new statement
	~AdapterForImageProduceDirect() {};
	void process() {
		data = ((ImageProduce*)ImaPtr)->data;
	}
};

#endif // __ADAPTERFORIMAGEPRODUCE_HPP__