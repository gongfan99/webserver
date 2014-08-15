#include <stdio.h>
#include "ImageProduce.h"

int main()
{
	char key;
	
	printf("I am here.");
	
	ImageProduce_ops IPo = {
		.process = &ImageProduce_process,
		.destroy = &ImageProduce_destroy
	};

	ImageProduce* ImageProduce1 = ImageProduce_create(&IPo);



    cvNamedWindow("Camera_Output", 1);    //Create window
	//IplImage stub, *dst_img;
	//dst_img = cvGetImage(ImageProduce1->data, &stub);


	
	printf("I am here.");
	
    while(1){ //Create infinte loop for live streaming
		ImageProduce1->ops->process(ImageProduce1);
		cvShowImage("Camera_Output", ImageProduce1->data);   //Show image frames on created window
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (key == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
	
    cvDestroyWindow("Camera_Output"); //Destroy Window
	ImageProduce1->ops->destroy(ImageProduce1);
    return 0;
}