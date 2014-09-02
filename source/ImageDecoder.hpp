#ifndef __IMAGEDECODER_HPP__
#define __IMAGEDECODER_HPP__

#include <cv.h>
#include <highgui.h>
#include <vector>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "Adapter.hpp"

namespace ozo {

class ImageDecoder {
public:
	Adapter* adapter; //external input interface
	std::vector<char> *data; //external output interface
	boost::mutex mutex; //external output interface
	
	ImageDecoder(Adapter* p) : adapter(p) {
		data = new std::vector<char>();
	}; 
	
	~ImageDecoder() {
		delete data;
	};	
};

} //namespace ozo

#endif // __IMAGEDECODER_HPP__