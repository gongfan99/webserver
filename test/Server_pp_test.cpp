#include <iostream>
#include <conio.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/chrono.hpp>
#include "Server_pp.hpp"
#include "SourceCamera.hpp"
#include "DecoderQR.hpp"
#include "utils.hpp"
#include "TestConfigure.hpp"

using namespace ozo;

boost::mutex mutexDone;
bool done = false;
	
void threadQRdecoder(SourceCamera &camera, DecoderQR &decoder) {
	while(1){ //event loop
		camera.process();
		decoder.process();
		{
			boost::lock_guard<boost::mutex> lock2(mutexDone);
			if (done) break;
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));
	}
}

int main()
{
	char key;

	//create components: camera and decoder
	SourceCamera camera;
	DecoderQR decoder;
	OculusDK2 oculus;
	Server_pp server;

	//link components
	decoder.source = &(camera.data);
	server.hmd = &(oculus.hmd);
	server.oculus_data = &(oculus.data);
	
	//process each component
	//camera.data = image; //use this instead of camera.process()
	camera.data = cv::cvarrToMat(cvLoadImage(OZO_TEST_FOLDER"/resource/qrcode.jpg", CV_LOAD_IMAGE_GRAYSCALE));
	std::cout << TEST_FOLDER"/resource/qrcode.jpg" << std::endl;
	decoder.process();

	//show result
	

	boost::thread t1(camera, decoder);

	while(1){ //main event loop
		oculus.process();
		server.process();
		if (_kbhit()) {
			key = _getch();
			std::cout << key;
		}
		if (key == 27){
			boost::lock_guard<boost::mutex> lock1(mutexDone);
			done = true;
			std::cout << done;
			break;      //If you hit ESC key loop will break.
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
	}
	
	t1.join();
}

/* #include <iostream>
#include <conio.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "utils.hpp"

typedef websocketpp::server<websocketpp::config::asio> server;
server print_server;
websocketpp::connection_hdl mHandle;
bool isConnected = false;

void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        std::cout << msg->get_payload() << std::endl;
		if (isConnected) print_server.send(mHandle, "{ \"m\" : \"default\", \"o\" : \"default\", \"a\" : \"default\" }", websocketpp::frame::opcode::TEXT);
}

void on_open(websocketpp::connection_hdl hdl) {
        mHandle = hdl;
		isConnected = true;
		std::cout << "connected..." << std::endl;
}

int main() {
	char key;
	int i;
    print_server.set_message_handler(&on_message);
	print_server.set_open_handler(&on_open);

    print_server.init_asio();
    print_server.listen(9002);
    print_server.start_accept();

	while(1){ //Create infinte loop for live streaming
		i = print_server.poll();
		if (i != 0) std::cout << "poll() executes: " << i << std::endl;
		if (_kbhit())
			key = _getch();
		ozo::sleep(100);
		if (key == 27){
			break;      //If you hit ESC key loop will break.
		}
	}
    //print_server.run();
} */