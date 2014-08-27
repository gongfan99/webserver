#include <iostream>
#include "Server_pp.hpp"

using namespace ozo;

int main()
{
	OculusDK2 *oculus = new OculusDK2;
	Server_pp *server = new Server_pp(oculus, (ImageDecoder *)NULL);
	
	std::cout << "I am here." << std::endl;
	server->process();
	std::cout << "I am here." << std::endl;
	delete server;
}