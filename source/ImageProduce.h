#ifndef __IMAGEPRODUCE_H__
#define __IMAGEPRODUCE_H__

#include <cv.h>
#include <highgui.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	//below are the member variables
	IplImage* data; //this is the external interface
}ImageProduce;

#ifdef __cplusplus
}
#endif

#endif // __IMAGEPRODUCE_H__