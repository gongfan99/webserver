#include <iostream>
#include <windows.h>
#include "ImageProduceCamera.h"
#include "Adapter.hpp"
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
	IplImage* image = cvCreateImageHeader(cvSize(width, height), IPL_DEPTH_8U, 1);
	cvSetData( image, buffer, width );

	//create an AdapterDirect object with buffer or image file
	AdapterDirect* Adapter2 = new AdapterDirect((ImageProduce*)NULL);
	Adapter2->data = image; //use this instead of Adapter2->process()
	//Adapter2->data = cvLoadImage("../source/qrcode.png", CV_LOAD_IMAGE_GRAYSCALE);

	ImageDecoderQR* decoder2 = new ImageDecoderQR(Adapter2);
	decoder2->process();
	
	std::vector<char> qrresult = *(decoder2->data);
	std::cout << "The QR code is: ";
	for( std::vector<char>::const_iterator i = qrresult.begin(); i != qrresult.end(); ++i)
		std::cout << *i;
	std::cout << std::endl << std::endl;
	
	delete Adapter2;
	delete decoder2;
	cvReleaseImageHeader(&image); //do not use cvReleaseImage since it will try to release "buffer"

	
	//test 2; using camera images
	ImageProduceCamera* ImageProduceCamera1 = ImageProduceCamera_create();
	AdapterDirect* Adapter1 = new AdapterDirect((ImageProduce*)ImageProduceCamera1);
	ImageDecoderQR* decoder1 = new ImageDecoderQR(Adapter1);
	
	int j;
    for (j=0; j<150; j++) { //Create infinte loop for live streaming
		ImageProduceCamera1->ops->process(ImageProduceCamera1);
		Adapter1->process();
		decoder1->process();
		//print out QR code
		qrresult = *(decoder1->data);
		std::cout << "The QR code is: ";
		for( std::vector<char>::const_iterator i = qrresult.begin(); i != qrresult.end(); ++i)
			std::cout << *i;
		std::cout << std::endl;
/* 		cv::Mat imageAdapter = cv::cvarrToMat(Adapter1->data);
		cv::imwrite(to_string<int>(j)+".jpg", imageAdapter); */
		if (showWindow) {
			cvShowImage("Camera_Output", Adapter1->data);   //Show image frames on created window
			key = cvWaitKey(10);     //Capture Keyboard stroke
			if (key == 27){
				break;      //If you hit ESC key loop will break.
			}
		}
		sleep(2000);
    }
	
	ImageProduceCamera1->ops->destroy(ImageProduceCamera1);
	delete Adapter1;
	delete decoder1;
	
    if (showWindow) cvDestroyWindow("Camera_Output"); //Destroy Window
    return 0;
}