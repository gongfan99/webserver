#include "utils.hpp"

#define LEGACY_CPLUSPLUS

#ifdef LEGACY_CPLUSPLUS

    #if defined(_WIN32) || defined(_WIN64)
        #include <Windows.h>
        namespace ozo
        {
             void sleep( unsigned int millisecs ) { ::Sleep(millisecs) ; }
        }

    #else // !_WIN32
        #include <unistd.h> 
        namespace ozo
        {
             void sleep( unsigned int millisecs ) { ::usleep( millisecs * 1000 ) ; }
        }
    #endif // _WIN32

#else // C++11
	#include <thread>
	#include <chrono>
	namespace ozo
	{
		void sleep( unsigned int millisecs ) 
		{ std::this_thread::sleep_for( std::chrono::milliseconds(millisecs) ) ; }
	}

#endif // LEGACY_CPLUSPLUS