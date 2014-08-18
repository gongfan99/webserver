#include <stdio.h>
#include "ImageProduceCamera.h"

#ifdef __cplusplus
extern "C" {
#endif

ImageProduceCamera* ImageProduceCamera_create(){
	ImageProduceCamera* this_ptr = (ImageProduceCamera*)malloc(sizeof(ImageProduceCamera));
	this_ptr->ops = (ImageProduceCamera_ops*)malloc(sizeof(ImageProduceCamera_ops));
	this_ptr->capture = cvCaptureFromCAM(0); //0=default, -1(CV_CAP_ANY)=any camera, 1..99=your camera
	if (!this_ptr->capture) {
		printf("No camera detected! Video file will be used.\n");
		this_ptr->capture = cvCaptureFromFile("../../../source/qrcode.avi");
	};
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