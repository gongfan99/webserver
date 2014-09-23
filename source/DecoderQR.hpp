#ifndef __OZO_DECODERQR_HPP__
#define __OZO_DECODERQR_HPP__

#include <cv.h>
#include <highgui.h>
#include <zxing/LuminanceSource.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <zxing/common/GreyscaleLuminanceSource.h>
#include <zxing/Exception.h>
#include <vector>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace ozo {

class DecoderQR {
public:
	cv::Mat *source; //external input interface
	std::vector<char> data; //external output interface
	boost::mutex mutex; //external interface; mutex for data
	DecoderQR();
	~DecoderQR();
	void process();
};

} //namespace ozo

#endif // __OZO_DECODERQR_HPP__