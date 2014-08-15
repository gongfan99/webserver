#include "ImageProduce.h"

#ifdef __cplusplus
extern "C" {
#endif

ImageProduce* ImageProduce_create(ImageProduce_ops* IPo_prt){
	ImageProduce* this_ptr = (ImageProduce*)malloc(sizeof(ImageProduce));
	this_ptr->ops = (ImageProduce_ops*)malloc(sizeof(ImageProduce_ops));
	this_ptr->capture = cvCaptureFromCAM(CV_CAP_ANY); //Capture using any camera connected to your system
	//this_ptr->capture = cvCaptureFromFile("C:/Users/Public/Videos/Sample Videos/Wildlife.wmv");
	*(this_ptr->ops) = *IPo_prt;
	return this_ptr;
}

void ImageProduce_process(ImageProduce* this_ptr){
	IplImage* frame = cvQueryFrame(this_ptr->capture); //Create image frames from capture
	//CvMat mathdr;
	this_ptr->data =  frame;//cvGetMat( frame, &mathdr );
}

void ImageProduce_destroy(ImageProduce* this_ptr){
	cvReleaseCapture(&(this_ptr->capture)); //Release capture.
	free(this_ptr->ops);
	free(this_ptr);
}

#ifdef __cplusplus
}
#endif