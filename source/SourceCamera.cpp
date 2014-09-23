#include "SourceCamera.hpp"
#include "utils.hpp"
#include "OzoConfigure.hpp"

#define OZO_PROJ_SRC_ STR(OZO_PROJ_SRC)

namespace ozo {

SourceCamera::SourceCamera() {
	cap.open(1);
	if (!cap.isOpened()) {
		std::cout << "camera cannot be opened; instead use " << OZO_PROJ_SRC_"/qrcode.avi" << std::endl;
		cap.open(OZO_PROJ_SRC_"/qrcode.avi");
	}
 /* 	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320); 
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);  */
}

SourceCamera::~SourceCamera() {}

void SourceCamera::process() {
	do {
		cap >> frame;
	} while (frame.empty()); //first frame from camera is often NULL
	cv::cvtColor(frame, data, CV_BGR2GRAY); //convert BGR to gray
}

} //namespace ozo