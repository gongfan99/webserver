#include <iostream>
#include "ImageProduceCamera.h"
#include "Adapter.hpp"

int main()
{
	using namespace ozo;
	char key;
    cvNamedWindow("Camera_Output", 1);    //Create window
	
	//std::cout << "I am here" << std::endl;
	
	ImageProduceCamera* camera = ImageProduceCamera_create();
	AdapterDirect* adapter = new AdapterDirect((ImageProduce*)camera);

    while(1){ //Create infinte loop for live streaming
		camera->ops->process(camera);
		adapter->process();
		cvShowImage("Camera_Output", adapter->data);   //Show image frames on created window
        key = cvWaitKey(500);     //Capture Keyboard stroke
        if (key == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
	
	camera->ops->destroy(camera);
	delete adapter;
	
    cvDestroyWindow("Camera_Output"); //Destroy Window
    return 0;
}