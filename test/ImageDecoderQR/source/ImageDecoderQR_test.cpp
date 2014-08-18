#include <iostream>
#include "ImageProduceCamera.h"
#include "Adapter.hpp"
#include "ImageDecoderQR.hpp"

using namespace ozo;

int main()
{
	char key;
    cvNamedWindow("Camera_Output", 1);    //Create window

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
	//std::cout << "I am here" << std::endl;
	
	//create an AdapterDirect object with buffer or image file
	AdapterDirect* Adapter2 = new AdapterDirect((ImageProduce*)NULL);
	//Adapter2->data = image; //use this instead of Adapter2->process()
	Adapter2->data = cvLoadImage("../source/qrcode.png", CV_LOAD_IMAGE_GRAYSCALE);
	cvShowImage("Camera_Output", Adapter2->data);   //Show image frames on created window	
	
	ImageDecoderQR* decoder2 = new ImageDecoderQR(Adapter2);
	decoder2->process();
	
	std::vector<char> qrresult = *(decoder2->data);
	std::cout << "The QR code is: ";
	for( std::vector<char>::const_iterator i = qrresult.begin(); i != qrresult.end(); ++i)
		std::cout << *i;
	
	delete Adapter2;
	delete decoder2;
	cvReleaseImage(&image);

	
/* 	//test 2; using camera images
	ImageProduceCamera* ImageProduceCamera1 = ImageProduceCamera_create();
	AdapterDirect* Adapter1 = new AdapterDirect((ImageProduce*)ImageProduceCamera1);
	ImageDecoderQR* decoder1 = new ImageDecoderQR(Adapter1);
	
    while(1){ //Create infinte loop for live streaming
		ImageProduceCamera1->ops->process(ImageProduceCamera1);
		Adapter1->process();
		decoder1->process();
		//print out QR code
		qrresult = *(decoder1->data);
		std::cout << "The QR code is: ";
		for( std::vector<char>::const_iterator i = qrresult.begin(); i != qrresult.end(); ++i)
			std::cout << *i;
		cvShowImage("Camera_Output", Adapter1->data);   //Show image frames on created window
        key = cvWaitKey(1000);     //Capture Keyboard stroke
        if (key == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
	
	ImageProduceCamera1->ops->destroy(ImageProduceCamera1);
	delete Adapter1;
	delete decoder1; */
	
    cvDestroyWindow("Camera_Output"); //Destroy Window
    return 0;
}