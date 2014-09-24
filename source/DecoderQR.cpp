#include "DecoderQR.hpp"

namespace ozo {

DecoderQR::DecoderQR() : result_text("") {}

DecoderQR::~DecoderQR() {}

void DecoderQR::process() {
	using namespace zxing;
	cv::Mat& image = *source;
	//image.data is uchar* per opencv and needs to be converted to char* for zxing use.
	ArrayRef<char> greyData((char*)image.data, image.rows*image.cols); 
	Ref<LuminanceSource> source(new GreyscaleLuminanceSource(greyData, image.step, image.rows, 0, 0, image.cols, image.rows));
	Ref<Binarizer> binarizer(new HybridBinarizer(source));
	Ref<BinaryBitmap> bitmap(new BinaryBitmap(binarizer));
	qrcode::QRCodeReader reader;
	Ref<Result> result(reader.decode(bitmap, DecodeHints(DecodeHints::TRYHARDER_HINT)));//+DecodeHints::DEFAULT_HINT)));
	result_text = result->getText()->getText();
	{
		boost::lock_guard<boost::mutex> lock1(mutex);
		data = result_text;
	}	
}

} //namespace ozo