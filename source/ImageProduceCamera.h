#ifndef __IMAGEPRODUCECAMERA_H__
#define __IMAGEPRODUCECAMERA_H__

#include "ImageProduce.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImageProduceCamera_ ImageProduceCamera;
//virtual function table
typedef struct {
	void (*process)(ImageProduceCamera* this_ptr);
	void (*destroy)(ImageProduceCamera* this_ptr);
}ImageProduceCamera_ops;

typedef struct ImageProduceCamera_ {
	ImageProduce _; //base class
	ImageProduceCamera_ops* ops;
	CvCapture* capture;
}ImageProduceCamera;

ImageProduceCamera* ImageProduceCamera_create();
void ImageProduceCamera_process(ImageProduceCamera* this_ptr);
void ImageProduceCamera_destroy(ImageProduceCamera* this_ptr);

#ifdef __cplusplus
}
#endif

#endif // __IMAGEPRODUCECAMERA_H__