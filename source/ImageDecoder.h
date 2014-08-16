#ifndef __IMAGEDECODER_HPP__
#define __IMAGEDECODER_HPP__

#include <cv.h>
#include <highgui.h>

class ImageDecoder {
	AdapterForImageProduce* adapter; //external input interface
	char* data; //external output interface
	ImageDecoder(AdapterForImageProduce* p) : adapter(p) {}; //cast needed in the new statement
	~ImageDecoder() {};
};

#endif // __IMAGEDECODER_H__