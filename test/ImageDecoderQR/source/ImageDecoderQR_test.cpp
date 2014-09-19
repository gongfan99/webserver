#include <iostream>
#include <windows.h>
#include "DirectCamera.hpp"
#include "ImageDecoderQR.hpp"
#include "utils.hpp"

using namespace ozo;

int main()
{
	char key;
	bool showWindow = false;
    if (showWindow) cvNamedWindow("Camera_Output", 1);    //Create window

	//test 1; use buffer image or file image
	unsigned char buffer[] = 
	{ 
		120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 
		120,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , 120,  0 ,  0 ,  0 ,  0 ,  0 , 120,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , 120, 
		120,  0 , 120, 120, 120, 120, 120,  0 , 120, 120,  0 , 120,  0 , 120, 120,  0 , 120, 120, 120, 120, 120,  0 , 120, 
		120,  0 , 120,  0 ,  0 ,  0 , 120,  0 , 120, 120,  0 ,  0 , 120, 120, 120,  0 , 120,  0 ,  0 ,  0 , 120,  0 , 120, 
		120,  0 , 120,  0 ,  0 ,  0 , 120,  0 , 120, 120,  0 ,  0 ,  0 , 120, 120,  0 , 120,  0 ,  0 ,  0 , 120,  0 , 120, 
		120,  0 , 120,  0 ,  0 ,  0 , 120,  0 , 120, 120, 120,  0 , 120,  0 , 120,  0 , 120,  0 ,  0 ,  0 , 120,  0 , 120, 
		120,  0 , 120, 120, 120, 120, 120,  0 , 120, 120, 120, 120,  0 ,  0 , 120,  0 , 120, 120, 120, 120, 120,  0 , 120, 
		120,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , 120,  0 , 120,  0 , 120,  0 , 120,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , 120, 
		120, 120, 120, 120, 120, 120, 120, 120, 120,  0 ,  0 ,  0 ,  0 ,  0 , 120, 120, 120, 120, 120, 120, 120, 120, 120, 
		120,  0 ,  0 , 120,  0 ,  0 , 120,  0 , 120, 120,  0 ,  0 , 120,  0 , 120,  0 , 120, 120, 120, 120, 120,  0 , 120, 
		120,  0 ,  0 ,  0 ,  0 ,  0 , 120, 120,  0 , 120, 120,  0 , 120,  0 , 120,  0 , 120,  0 ,  0 ,  0 , 120, 120, 120, 
		120, 120, 120, 120, 120, 120, 120,  0 , 120,  0 ,  0 ,  0 , 120, 120,  0 ,  0 , 120,  0 , 120,  0 ,  0 ,  0 , 120, 
		120, 120, 120,  0 ,  0 , 120, 120, 120,  0 ,  0 ,  0 , 120,  0 , 120, 120, 120, 120, 120, 120,  0 , 120, 120, 120, 
		120,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , 120, 120,  0 , 120, 120, 120, 120,  0 , 120, 120,  0 , 120,  0 , 120, 120, 
		120, 120, 120, 120, 120, 120, 120, 120, 120,  0 ,  0 , 120,  0 ,  0 , 120, 120, 120, 120,  0 , 120,  0 ,  0 , 120, 
		120,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , 120, 120, 120,  0 , 120,  0 ,  0 ,  0 ,  0 ,  0 , 120,  0 , 120, 120, 120, 
		120,  0 , 120, 120, 120, 120, 120,  0 , 120, 120,  0 ,  0 ,  0 ,  0 ,  0 , 120,  0 ,  0 ,  0 ,  0 , 120, 120, 120, 
		120,  0 , 120,  0 ,  0 ,  0 , 120,  0 , 120,  0 , 120, 120,  0 ,  0 , 120,  0 ,  0 , 120,  0 , 120,  0 ,  0 , 120, 
		120,  0 , 120,  0 ,  0 ,  0 , 120,  0 , 120,  0 , 120,  0 ,  0 ,  0 , 120, 120, 120, 120, 120, 120, 120, 120, 120, 
		120,  0 , 120,  0 ,  0 ,  0 , 120,  0 , 120, 120,  0 ,  0 , 120, 120, 120,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , 120, 
		120,  0 , 120, 120, 120, 120, 120,  0 , 120,  0 , 120,  0 , 120, 120,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , 120, 
		120,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , 120,  0 , 120,  0 ,  0 , 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 
		120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120
	}; 
	int width = 23; 
	int height = 23;
	cv::Mat image(height, width, CV_8UC(1), buffer);

	//create camera and decoder
	DirectCamera* camera = new DirectCamera();
	ImageDecoderQR* decoder = new ImageDecoderQR(camera);
	
	*(camera->data) = image; //use this instead of camera->process()
	//*(camera->data) = cv::cvarrToMat(cvLoadImage("./qrcode.png", CV_LOAD_IMAGE_GRAYSCALE));
	decoder->process();
	
	std::vector<char> qrresult = *(decoder->data);
	std::cout << "The QR code is: ";
	for( std::vector<char>::const_iterator i = qrresult.begin(); i != qrresult.end(); ++i)
		std::cout << *i;
	std::cout << std::endl << std::endl;

	
	//test 2; using camera images
	int j;
    for (j=0; j<0; j++) { //Create infinte loop for live streaming
		camera->process();
		decoder->process();
		//print out QR code
		qrresult = *(decoder->data);
		std::cout << "The QR code is: ";
		for( std::vector<char>::const_iterator i = qrresult.begin(); i != qrresult.end(); ++i)
			std::cout << *i;
		std::cout << std::endl;
/* 		cv::imwrite(to_string<int>(j)+".jpg", *(camera->data)); */
		if (showWindow) {
			cvShowImage("Camera_Output", camera->data);   //Show image frames on created window
			key = cvWaitKey(10);     //Capture Keyboard stroke
			if (key == 27){
				break;      //If you hit ESC key loop will break.
			}
		}
		sleep(2000);
    }

	delete camera;
	delete decoder;
	
    if (showWindow) cvDestroyWindow("Camera_Output"); //Destroy Window
    return 0;
}