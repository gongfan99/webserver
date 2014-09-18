#include <iostream>
#include "DirectCamera.hpp"

int main()
{
	using namespace ozo;
	char key;
    cvNamedWindow("Camera_Output", 1);    //Create window
	
	//std::cout << "I am here" << std::endl;
	
	DirectCamera* camera = new DirectCamera();

    while(1){ //Create infinte loop for live streaming
		camera->process();
		imshow("Camera_Output", *(camera->data));   //Show image frames on created window
        key = cvWaitKey(1000);     //Capture Keyboard stroke
        if (key == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
	
	delete camera;
	
    cvDestroyWindow("Camera_Output"); //Destroy Window

    return 0;
}