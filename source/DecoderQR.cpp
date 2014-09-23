#include "DecoderQR.hpp"

namespace ozo {

DecoderQR::DecoderQR() {
	data.reserve(10);
}

DecoderQR::~DecoderQR() {
	std::vector<char>().swap(data); //release memory of "data"
}

void DecoderQR::process() {

	std::string result_text = "";
	try
	{
		using namespace zxing;
		cv::Mat& image = *source;
		ArrayRef<char> greyData((char*)image.data, image.rows*image.cols); //image.data is uchar* per opencv and needs to be converted to char* for zxing use.
		Ref<LuminanceSource> source(new GreyscaleLuminanceSource(greyData, image.step, image.rows, 0, 0, image.cols, image.rows));
		Ref<Binarizer> binarizer(new HybridBinarizer(source));
		Ref<BinaryBitmap> bitmap(new BinaryBitmap(binarizer));
		qrcode::QRCodeReader reader;
		Ref<Result> result(reader.decode(bitmap, DecodeHints(DecodeHints::TRYHARDER_HINT)));//+DecodeHints::DEFAULT_HINT)));
		result_text = result->getText()->getText();
	}
	catch (zxing::Exception& e)
	{
		std::cerr << "Error: " << e.what() << ";   " ;
	}
	{
		boost::lock_guard<boost::mutex> lock1(mutex);
		std::vector<char>().swap(data); //clear data
		std::copy(result_text.begin(), result_text.end(), back_inserter(data)); //assign result_text to data
	}	
}

} //namespace ozo