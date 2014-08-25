#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "Oculus.hpp"
#include "ImageDecoder.hpp"

namespace ozo {

class Server {
public:
	//all are external input interfaces
	Oculus *oculus;
	ImageDecoder *decoder;

	Server() {}; 
	~Server() {};	
};

} //namespace ozo

#endif // __SERVER_HPP__