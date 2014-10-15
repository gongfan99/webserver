#ifndef __OZO_UTILS_HPP__
#define __OZO_UTILS_HPP__

#include <string>
#include <fstream>
#include <sstream>
#include "OVR_CAPI.h"

namespace ozo
{ 
    void sleep( unsigned int millisecs );

	std::string meshString(ovrDistortionMesh** const &meshData);
	
	template < typename T >
	std::string to_string( const T& n )	{
		std::ostringstream stm ;
		stm << n ;
		return stm.str() ;
	}
}

#endif // __OZO_UTILS_HPP__