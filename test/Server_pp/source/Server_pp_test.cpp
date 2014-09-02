#include <iostream>
#include <conio.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "Server_pp.hpp"
#include "ImageProduceCamera.h"
#include "Adapter.hpp"
#include "ImageDecoderQR.hpp"
#include "utils.hpp"

using namespace ozo;

boost::mutex mutexQRdecoder;
boost::mutex mutexDone;
bool done = false;
	
void threadQRdecoder(ImageProduceCamera* &ImageProduceCamera1,
					AdapterDirect* &Adapter1,
					ImageDecoderQR* &decoder1) {
	while(1){ //Create event loop
		ImageProduceCamera1->ops->process(ImageProduceCamera1);
		Adapter1->process();
		{
			boost::lock_guard<boost::mutex> lock1(mutexQRdecoder);
			decoder1->process();
		};
		{
			boost::lock_guard<boost::mutex> lock2(mutexDone);
			if (done) break;
		}
		sleep(5000);
	}
}

int main()
{
	char key;

	ImageProduceCamera* ImageProduceCamera1 = ImageProduceCamera_create();
	AdapterDirect* Adapter1 = new AdapterDirect((ImageProduce*)ImageProduceCamera1);
	ImageDecoderQR* decoder1 = new ImageDecoderQR(Adapter1);	
	OculusDK2 *oculus = new OculusDK2;
	Server_pp *server = new Server_pp(oculus, decoder1);//(ImageDecoder *)NULL

	boost::thread t1(threadQRdecoder, ImageProduceCamera1, Adapter1, decoder1);
	
	while(1){ //Create event loop
		ImageProduceCamera1->ops->process(ImageProduceCamera1);
		Adapter1->process();
		decoder1->process();
		oculus->process();
		{
			boost::lock_guard<boost::mutex> lock1(mutexQRdecoder);
			server->process();
		}
		if (_kbhit()) {
			key = _getch();
			std::cout << key;
		}
		sleep(3000);
		if (key == 27){
			boost::lock_guard<boost::mutex> lock2(mutexDone);
			done = true;
			break;      //If you hit ESC key loop will break.
		}
	}
	
	t1.join();

	delete server;
	delete oculus;
	delete decoder1;
	delete Adapter1;
	ImageProduceCamera1->ops->destroy(ImageProduceCamera1);
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