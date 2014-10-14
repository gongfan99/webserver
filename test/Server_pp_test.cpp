#include <iostream>
#include <conio.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/chrono.hpp>
#include "SourceCamera.hpp"
#include "DecoderQR.hpp"
#include "OculusDK2.hpp"
#include "Server_pp.hpp"
#include "utils.hpp"
#include "OzoConfigure.hpp"

using namespace ozo;

boost::mutex mutexDone;
bool done = false;
	
void threadQRdecoder(SourceCamera *camera, DecoderQR *decoder) { //DecoderQR has mutex member; only pointer is allowed here
	//always avoid put "break" statement inside boost::lock_guard<boost::mutex> scope
	bool done2 = false;
	while(1){ //event loop
		try	{
			camera->process();
			decoder->process();
		} catch (zxing::Exception& e) {
			//if decoder fails to process, it will not cause other issue so can be ignored.
			std::cerr << "Error: " << e.what() << ";   " ;
		}
		std::cout << "The QR code is: " << decoder->data << std::endl;
		{
			boost::lock_guard<boost::mutex> lock2(mutexDone);
			done2 = done;
		}
		if (done2) break;
		boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));
	}
}

int main()
{
	char key;

	//create components
	SourceCamera camera;
	DecoderQR decoder;
	OculusDK2 oculus;
	Server_pp server;

	//connect components
	decoder.source = &(camera.data);
	server.mutex = &(decoder.mutex);
	server.decoder_data = &(decoder.data);
	server.hmd = &(oculus.hmd);
	server.oculus_data = &(oculus.data);
	server.meshData[0] = &(oculus.meshData[0]);
	server.meshData[1] = &(oculus.meshData[1]);

	//create another thread to run the QR decoding
	boost::thread t1(threadQRdecoder, &camera, &decoder);

	//main event loop
	while(1){
		oculus.process();
		server.process();
		if (_kbhit()) {
			key = _getch();
			std::cout << key;
		}
		if (key == 27){
			boost::lock_guard<boost::mutex> lock1(mutexDone);
			done = true;
		}
		if (done) break;      //If you hit ESC key loop will break.
		boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
	}
	
	std::cout << "\nMain event loop terminated." << std::endl;	
	t1.join();
	std::cout << "\nProgram terminated." << std::endl;
}