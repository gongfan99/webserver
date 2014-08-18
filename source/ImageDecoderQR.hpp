#ifndef __IMAGEDECODERQR_HPP__
#define __IMAGEDECODERQR_HPP__

#include <cv.h>
#include <highgui.h>
#include "ImageDecoder.hpp"
#include <zxing/LuminanceSource.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <zxing/common/GreyscaleLuminanceSource.h>
#include <zxing/Exception.h>

namespace ozo {

class ImageDecoderQR : public ImageDecoder {
public:
	ImageDecoderQR(Adapter* p);
	~ImageDecoderQR();
	void process();
};

} //namespace ozo

#endif // __IMAGEDECODERQR_HPP__