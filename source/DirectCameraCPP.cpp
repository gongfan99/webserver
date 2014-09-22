#include "DirectCameraCPP.hpp"

namespace ozo {

DirectCameraCPP::DirectCameraCPP() {
	cap.open(1);
	if (!cap.isOpened()) { 
		cap.open("../../../source/qrcode.avi");
	}
 /* 	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320); 
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);  */
}

DirectCameraCPP::~DirectCameraCPP() {}

void DirectCameraCPP::process() {
	do {
		cap >> frame; //capture an image;
	} while (frame.empty()); //first frame from camera is often NULL
	cv::cvtColor(frame, data, CV_BGR2GRAY); //convert RGB to gray
}

} //namespace ozo