#ifndef __OZO_UTILS_HPP__
#define __OZO_UTILS_HPP__

#define QUOTEME(x) #x
#define STR(macro) QUOTEME(macro)

#include <string>
#include <sstream>

namespace ozo
{ 
    void sleep( unsigned int millisecs );
	
	template < typename T >
	std::string to_string( const T& n )	{
		std::ostringstream stm ;
		stm << n ;
		return stm.str() ;
	}
}

#endif // __OZO_UTILS_HPP__