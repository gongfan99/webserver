#include <iostream>
#include "ImageProduceCamera.h"
#include "Adapter.hpp"

using namespace ozo;

int main()
{
	char key;
    cvNamedWindow("Camera_Output", 1);    //Create window
	
	//std::cout << "I am here" << std::endl;
	
	ImageProduceCamera* ImageProduceCamera1 = ImageProduceCamera_create();
	AdapterDirect* Adapter1 = new AdapterDirect((ImageProduce*)ImageProduceCamera1);

    while(1){ //Create infinte loop for live streaming
		ImageProduceCamera1->ops->process(ImageProduceCamera1);
		Adapter1->process();
		cvShowImage("Camera_Output", Adapter1->data);   //Show image frames on created window
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (key == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
	
	ImageProduceCamera1->ops->destroy(ImageProduceCamera1);
	delete Adapter1;
	
    cvDestroyWindow("Camera_Output"); //Destroy Window
    return 0;
}