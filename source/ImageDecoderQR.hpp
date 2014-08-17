#ifndef __IMAGEDECODERQR_HPP__
#define __IMAGEDECODERQR_HPP__

#include <cv.h>
#include <highgui.h>
#include "ImageDecoder.hpp"

#include <zxing/LuminanceSource.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/oned/OneDReader.h>
#include <zxing/oned/EAN8Reader.h>
#include <zxing/oned/EAN13Reader.h>
#include <zxing/oned/Code128Reader.h>
#include <zxing/datamatrix/DataMatrixReader.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/aztec/AztecReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/GreyscaleLuminanceSource.h>
#include <zxing/Exception.h>

namespace ozo {

class ImageDecoderQR : public ImageDecoder {
public:
	ImageDecoderQR(AdapterForImageProduce* p) : ImageDecoder(p) {
		(*data).reserve(10);
	};
	
	~ImageDecoderQR() {
		std::vector<char>().swap(*data);
	};
	
	void process() {

		try
		{
			using namespace zxing;
			cv::Mat image = cv::cvarrToMat(adapter->data);
			ArrayRef<uchar> greyData(image.data, 23*23);
			Ref<LuminanceSource> source(new GreyscaleLuminanceSource(greyData, image.step, image.rows, 0, 0, image.cols, image.rows));
			//Ref<OpenCVBitmapSource> source(new OpenCVBitmapSource(image));
			Ref<Binarizer> binarizer(new GlobalHistogramBinarizer(source));
			Ref<BinaryBitmap> bitmap(new BinaryBitmap(binarizer));
			Ref<Result> result(reader->decode(bitmap, DecodeHints(DecodeHints::TRYHARDER_HINT)));//+DecodeHints::DEFAULT_HINT)));
			std::copy(result->getText()->begin(), result->getText()->end(), back_inserter(*data));
			cout << result->getText()->getText() << endl;
				//Export the read barcode here
		}
		catch (zxing::Exception& e)
		{
				//Export your failure to read the code here
			cerr << "Error: " << e.what() << endl;
		}
	}
};

};

} //namespace ozo

#endif // __IMAGEDECODERQR_HPP__