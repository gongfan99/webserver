#ifndef __IMAGEPRODUCE_H__
#define __IMAGEPRODUCE_H__

#include <cv.h>
#include <highgui.h>

#ifdef __cplusplus
extern "C" {
#endif

#define atomic_t int

typedef struct ImageProduce_ ImageProduce;
typedef struct ImageProduce_ops_ ImageProduce_ops;

ImageProduce* ImageProduce_create(ImageProduce_ops* IPo_prt);
void ImageProduce_process(ImageProduce* this_ptr);
void ImageProduce_destroy(ImageProduce* this_ptr);

//vtable
struct ImageProduce_ops_ {
	void (*process)(ImageProduce* this_ptr);
	void (*destroy)(ImageProduce* this_ptr);
};

struct ImageProduce_ {
	atomic_t ref_count;
	CvCapture* capture;
	IplImage* data;
	ImageProduce_ops* ops;
};

#ifdef __cplusplus
}
#endif

#endif // __IMAGEPRODUCE_H__