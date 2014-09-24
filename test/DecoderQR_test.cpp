#include <iostream>
#include <windows.h>
#include "SourceCamera.hpp"
#include "DecoderQR.hpp"
#include "utils.hpp"
#include "OzoConfigure.hpp"

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

	//connect components
	decoder.source = &(camera.data);

	//process each component
	//camera.data = image; //use this instead of camera.process()
	std::cout << OZO_TEST_SOURCE_DIR"/resource/qrcode.jpg" << std::endl;
	camera.data = cv::cvarrToMat(cvLoadImage(OZO_TEST_SOURCE_DIR"/resource/qrcode.jpg", CV_LOAD_IMAGE_GRAYSCALE));
	try {
		decoder.process();
	} catch (zxing::Exception& e) {
			std::cerr << "Error: " << e.what() << ";   " ;
	}

	//show result
	std::cout << "The QR code is: " << decoder.data << std::endl;


	//test 2; using camera images
	int j;
    for (j=0; j<3; j++) { //Create infinte loop for live streaming
		try	{
			camera.process();
			decoder.process();
		} catch (zxing::Exception& e) {
			//if decoder fails to process, it will not cause other issue so can be ignored.
			std::cerr << "Error: " << e.what() << ";   " ;
		}
		//print out QR code
		std::cout << "The QR code is: " << decoder.data << std::endl;
		//cv::imwrite(to_string<int>(j)+".jpg", *(camera->data));
		if (showWindow) {
			cv::imshow("Camera_Output", camera.data);    //Show image frames on created window
			key = cv::waitKey(10);     //Capture Keyboard stroke
			if (key == 27){
				break;      //If you hit ESC key loop will break.
			}
		}
		sleep(1000);
    }

    if (showWindow) cv::destroyWindow("Camera_Output"); //Destroy Window
    return 0;
}
