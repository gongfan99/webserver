#include "DirectCamera.hpp"

namespace ozo {

DirectCamera::DirectCamera() {
	camera = ImageProduceCamera_create();
	adapter = new AdapterDirect((ImageProduce*)camera);
	data = new cv::Mat(cv::cvarrToMat(adapter->data));
	//*data = cv::cvarrToMat(adapter->data); //convert IplImage to cv::Mat
}

DirectCamera::~DirectCamera() {
	camera->ops->destroy(camera);
	delete adapter;
	delete data;
}

void DirectCamera::process() {
	camera->ops->process(camera);
	adapter->process();
}

} //namespace ozo