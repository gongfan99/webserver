#include <stdio.h>
#include "ImageProduceCamera.h"

int main()
{
	char key;
	
	//printf("I am here.");
	
	ImageProduceCamera* ImageProduceCamera1 = ImageProduceCamera_create();

    cvNamedWindow("Camera_Output", 1);    //Create window

    while(1){ //Create infinte loop for live streaming
		ImageProduceCamera1->ops->process(ImageProduceCamera1);
		cvShowImage("Camera_Output", ((ImageProduce*)ImageProduceCamera1)->data);   //Show image frames on created window
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (key == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
	
    cvDestroyWindow("Camera_Output"); //Destroy Window
	ImageProduceCamera1->ops->destroy(ImageProduceCamera1);
    return 0;
}