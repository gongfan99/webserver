#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "OculusBase.hpp"
#include "ImageDecoder.hpp"

namespace ozo {

class Server {
public:
	//all are external input interfaces
	OculusBase *oculus;
	ImageDecoder *decoder;

	Server(OculusBase *o, ImageDecoder *d) : oculus(o), decoder(d) {}; 
	~Server() {};	
};

} //namespace ozo

#endif // __SERVER_HPP__