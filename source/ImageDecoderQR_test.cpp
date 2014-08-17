#include <iostream>
#include "ImageProduceCamera.h"
#include "AdapterForImageProduce.hpp"
#include "ImageDecoderQR.hpp"

using namespace ozo;

int main()
{
	char key;
    cvNamedWindow("Camera_Output", 1);    //Create window

	//unsigned char
	char buffer[] = 
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
	
	//ImageProduceCamera* ImageProduceCamera1 = ImageProduceCamera_create();
	AdapterForImageProduceDirect* Adapter1 = new AdapterForImageProduceDirect((ImageProduce*)NULL);
	Adapter1.data = image; //use this instead of Adapter1->process()
	cvShowImage("Camera_Output", Adapter1->data);   //Show image frames on created window	
	
	ImageDecoderQR* decoder = new ImageDecoderQR(Adapter1);
	decoder->process();
	
	path = *(decoder->data);
	for( std::vector<char>::const_iterator i = path.begin(); i != path.end(); ++i)
		std::cout << *i << ' ';
	
	//ImageProduceCamera1->ops->destroy(ImageProduceCamera1);
	delete Adapter1;
	delete decoder;
	
    cvDestroyWindow("Camera_Output"); //Destroy Window
    return 0;
}