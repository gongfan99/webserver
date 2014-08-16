#include "ImageProduceCamera.h"

#ifdef __cplusplus
extern "C" {
#endif

ImageProduceCamera* ImageProduceCamera_create(){
	ImageProduceCamera* this_ptr = (ImageProduceCamera*)malloc(sizeof(ImageProduceCamera));
	this_ptr->ops = (ImageProduceCamera_ops*)malloc(sizeof(ImageProduceCamera_ops));
	//this_ptr->capture = cvCaptureFromCAM(CV_CAP_ANY); //Capture using any camera connected to your system
	this_ptr->capture = cvCaptureFromFile("C:/Users/Public/Videos/Sample Videos/Wildlife.wmv");

	*(this_ptr->ops) = (ImageProduceCamera_ops){
		.process = &ImageProduceCamera_process,
		.destroy = &ImageProduceCamera_destroy
	};
	return this_ptr;
}

void ImageProduceCamera_process(ImageProduceCamera* this_ptr){
	((ImageProduce*)this_ptr)->data = cvQueryFrame(this_ptr->capture); //Create image frames from capture
}

void ImageProduceCamera_destroy(ImageProduceCamera* this_ptr){
	cvReleaseCapture(&(this_ptr->capture)); //Release capture.
	free(this_ptr->ops);
	free(this_ptr);
}

#ifdef __cplusplus
}
#endif