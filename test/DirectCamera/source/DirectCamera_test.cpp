#include <iostream>
//#include "DirectCamera.hpp"
/* #include "ImageProduceCamera.h"
#include "Adapter.hpp" */

namespace ozo {

class DirectCamera {
public:
	DirectCamera();
	~DirectCamera();
	void process();
};

DirectCamera::DirectCamera() {
	int *i;
	int j;
	i = &j;
	std::cout << "1" << std::endl;
	//i = new (std::nothrow) int;
	//std::cout << "2" << std::endl;
/* 	if (j == NULL) {
		std::cout << "new failed" << std::endl;
	} */
	//adapter = new AdapterDirect((ImageProduce*)NULL);
/* 	camera = ImageProduceCamera_create();
	adapter = new AdapterDirect((ImageProduce*)camera);
	data = new cv::Mat(cv::cvarrToMat(adapter->data)); */
	//*data = cv::cvarrToMat(adapter->data); //convert IplImage to cv::Mat
}

DirectCamera::~DirectCamera() {
	//camera->ops->destroy(camera);
	//delete adapter;
	//delete data;
}

void DirectCamera::process() {
/* 	camera->ops->process(camera);
	adapter->process(); */
	std::cout << "1" << std::endl;
}

} //namespace ozo

using namespace ozo;

int main()
{
/* 	char key;
    cvNamedWindow("Camera_Output", 1);    //Create window
	
	//std::cout << "I am here" << std::endl;
	
	//DirectCamera* camera = new DirectCamera();

    while(1){ //Create infinte loop for live streaming
		//camera->process();
		//cvShowImage("Camera_Output", camera->data);   //Show image frames on created window
        key = cvWaitKey(1000);     //Capture Keyboard stroke
        if (key == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
	
	//delete camera;
	
    cvDestroyWindow("Camera_Output"); //Destroy Window */
	DirectCamera* camera = new DirectCamera();
	camera->process();
	std::cout << "2" << std::endl;
    return 0;
}