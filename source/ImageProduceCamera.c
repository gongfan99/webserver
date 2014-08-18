#include <stdio.h>
#include "ImageProduceCamera.h"

#ifdef __cplusplus
extern "C" {
#endif

ImageProduceCamera* ImageProduceCamera_create(){
	ImageProduceCamera* this_ptr = (ImageProduceCamera*)malloc(sizeof(ImageProduceCamera));
	this_ptr->ops = (ImageProduceCamera_ops*)malloc(sizeof(ImageProduceCamera_ops));
	//this_ptr->capture = cvCaptureFromCAM(CV_CAP_ANY); //Capture using any camera connected to your system
	this_ptr->capture = cvCaptureFromFile("C:/Users/Public/Videos/Sample Videos/Wildlife.wmv");

	CvSize size;
	size.width = (int)cvGetCaptureProperty(this_ptr->capture, CV_CAP_PROP_FRAME_WIDTH);
	size.height = (int)cvGetCaptureProperty(this_ptr->capture, CV_CAP_PROP_FRAME_HEIGHT);
	printf("%f \n", cvGetCaptureProperty(this_ptr->capture, CV_CAP_PROP_FORMAT));
	printf("%d %d \n", size.width, size.height);
	((ImageProduce*)this_ptr)->data = cvCreateImage(size,IPL_DEPTH_8U,1); //reserve place for greyscale image
	
	*(this_ptr->ops) = (ImageProduceCamera_ops){
		.process = &ImageProduceCamera_process,
		.destroy = &ImageProduceCamera_destroy
	};
	return this_ptr;
}

void ImageProduceCamera_process(ImageProduceCamera* this_ptr){
	IplImage* frame;
	frame = cvQueryFrame(this_ptr->capture); //Create image frames from capture
	int i = frame->depth;
	int j = frame->nChannels;
	printf("frame format: %d %d\n", i, j);
	//printf("I am here.");
	cvCvtColor(frame, ((ImageProduce*)this_ptr)->data, CV_BGR2GRAY); //convert RGB to grey
	((ImageProduce*)this_ptr)->data = frame;
	//printf("I am here.");
}

void ImageProduceCamera_destroy(ImageProduceCamera* this_ptr){
	cvReleaseCapture(&(this_ptr->capture)); //Release capture.
	//cvReleaseImage(&(((ImageProduce*)this_ptr)->data));
	free(this_ptr->ops);
	free(this_ptr);
}

#ifdef __cplusplus
}
#endif