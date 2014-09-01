#include <iostream>
#include <conio.h>
#include "Server_pp.hpp"
#include "utils.hpp"

using namespace ozo;

int main()
{
	char key;
	OculusDK2 *oculus = new OculusDK2;
	Server_pp *server = new Server_pp(oculus, (ImageDecoder *)NULL);

	while(1){ //Create event loop
		server->process();
		if (_kbhit()) {
			key = _getch();
			std::cout << key;
		}
		sleep(3000);
		if (key == 27){
			break;      //If you hit ESC key loop will break.
		}
	}

	delete server;
	delete oculus;
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