#include <stdio.h>
#include "ImageProduceCamera.h"

#ifdef __cplusplus
extern "C" {
#endif

ImageProduceCamera* ImageProduceCamera_create(){
	ImageProduceCamera* this_ptr = (ImageProduceCamera*)malloc(sizeof(ImageProduceCamera));
	this_ptr->ops = (ImageProduceCamera_ops*)malloc(sizeof(ImageProduceCamera_ops));
	//this_ptr->capture = cvCaptureFromCAM(0); //CV_CAP_ANY : Capture using any camera connected to your system
	this_ptr->capture = cvCaptureFromFile("C:/Users/fgong/Downloads/ServerApp/webserver/source/qrcode.avi");

	CvSize size;
	size.width = (int)cvGetCaptureProperty(this_ptr->capture, CV_CAP_PROP_FRAME_WIDTH);
	size.height = (int)cvGetCaptureProperty(this_ptr->capture, CV_CAP_PROP_FRAME_HEIGHT);
	((ImageProduce*)this_ptr)->data = cvCreateImage(size,IPL_DEPTH_8U,1); //reserve place for greyscale image
	
	*(this_ptr->ops) = (ImageProduceCamera_ops){
		.process = &ImageProduceCamera_process,
		.destroy = &ImageProduceCamera_destroy
	};
	return this_ptr;
}

void ImageProduceCamera_process(ImageProduceCamera* this_ptr){
	IplImage* frame;
	do {
		frame = cvQueryFrame(this_ptr->capture); //capture an image
	} while (frame == NULL); //first frame from camera is often NULL
	cvCvtColor(frame, ((ImageProduce*)this_ptr)->data, CV_BGR2GRAY); //convert RGB to grey
}

void ImageProduceCamera_destroy(ImageProduceCamera* this_ptr){
	cvReleaseCapture(&(this_ptr->capture)); //Release capture.
	cvReleaseImage(&(((ImageProduce*)this_ptr)->data));
	free(this_ptr->ops);
	free(this_ptr);
}

#ifdef __cplusplus
}
#endif