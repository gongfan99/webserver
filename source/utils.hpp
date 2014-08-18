#ifndef __UTILS_HPP__
#define __UTILS_HPP__

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

#endif // __UTILS_HPP__