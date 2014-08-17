#ifndef __IMAGEDECODER_HPP__
#define __IMAGEDECODER_HPP__

#include <cv.h>
#include <highgui.h>
#include <vector>

namespace ozo {

class ImageDecoder {
public:
	AdapterForImageProduce* adapter; //external input interface
	std::vector<char> *data; //external output interface
	
	ImageDecoder(AdapterForImageProduce* p) : adapter(p) {
		data = new std::vector<char>();
	}; 
	
	~ImageDecoder() {
		delete data;
	};	
};

} //namespace ozo

#endif // __IMAGEDECODER_H__