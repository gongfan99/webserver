#ifndef __IMAGEDECODER_HPP__
#define __IMAGEDECODER_HPP__

#include <cv.h>
#include <highgui.h>

class ImageDecoderQR : public ImageDecoder {
public:
	AdapterForImageProduceDirect(ImageProduce* p) : AdapterForImageProduce(p) {}; //cast needed in the new statement
	~AdapterForImageProduceDirect() {};
	void process() {
		data = ((ImageProduce*)ImaPtr)->data;
	}
};

};

#endif // __IMAGEDECODER_H__