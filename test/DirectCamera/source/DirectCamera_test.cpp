#include <iostream>
#include "DirectCamera.hpp"

int main()
{
	using namespace ozo;
	char key;
	DirectCamera* camera = new DirectCamera();
	//std::cout << "I am here" << std::endl;
	
/*     cvNamedWindow("Camera_Output", 1);    //Create window
    while(1){ //Create infinte loop for live streaming
		camera->process();
		imshow("Camera_Output", *(camera->data));   //Show image frames on created window
        key = cvWaitKey(1000);     //Capture Keyboard stroke
        if (key == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
	cvDestroyWindow("Camera_Output"); //Destroy Window */

	cv::namedWindow("Camera_Output", CV_WINDOW_AUTOSIZE); 
	while (cv::waitKey(500) != 27) { 
		camera->process();; 
		cv::imshow("Camera_Output", *(camera->data)); 
	} 
	
	delete camera;
    cv::destroyWindow("Camera_Output"); //Destroy Window

    return 0;
}