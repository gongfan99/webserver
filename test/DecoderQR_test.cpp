#include <iostream>
#include <windows.h>
#include "SourceCamera.hpp"
#include "DecoderQR.hpp"
#include "utils.hpp"
#include "TestConfigure.hpp"

#define OZO_TEST_FOLDER STR(PROJECT_SOURCE_DIR)

using namespace ozo;

int main()
{
	char key;
	bool showWindow = 0;
    if (showWindow) cv::namedWindow("Camera_Output", CV_WINDOW_AUTOSIZE);     //Create window

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

	//create components: camera and decoder
	SourceCamera camera;
	DecoderQR decoder;

	//link components
	decoder.source = &(camera.data);
	
	//process each component
	//camera.data = image; //use this instead of camera.process()
	camera.data = cv::cvarrToMat(cvLoadImage(OZO_TEST_FOLDER"/resource/qrcode.jpg", CV_LOAD_IMAGE_GRAYSCALE));
	std::cout << OZO_TEST_FOLDER"/resource/qrcode.jpg" << std::endl;
	decoder.process();

	//show result
    std::vector<char> qrresult;
	qrresult = decoder.data;
	std::cout << "The QR code is: ";
	for( std::vector<char>::const_iterator i = qrresult.begin(); i != qrresult.end(); ++i)
		std::cout << *i;
	std::cout << std::endl << std::endl;


/* 	//test 2; using camera images
	int j;
    for (j=0; j<100; j++) { //Create infinte loop for live streaming
		camera.process();
		decoder.process();
		//print out QR code
		qrresult = decoder.data;
		std::cout << "The QR code is: ";
		for( std::vector<char>::const_iterator i = qrresult.begin(); i != qrresult.end(); ++i)
			std::cout << *i;
		std::cout << std::endl;
		//cv::imwrite(to_string<int>(j)+".jpg", *(camera->data));
		if (showWindow) {
			cv::imshow("Camera_Output", camera.data);    //Show image frames on created window
			key = cv::waitKey(10);     //Capture Keyboard stroke
			if (key == 27){
				break;      //If you hit ESC key loop will break.
			}
		}
		sleep(1000);
    } */

    if (showWindow) cv::destroyWindow("Camera_Output"); //Destroy Window
    return 0;
}
