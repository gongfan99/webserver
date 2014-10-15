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

namespace ozo
{
	std::string meshString(ovrDistortionMesh** const &meshData) {
		int i,j;
		std::ostringstream tempString;
		tempString << "{\n\"m\" : \"mesh\", \n";
		for ( j = 0; j < 2; ++j ) {
			if ( j == 0 ) {
				tempString << "\"left\" : { \"VertexCount\" : ";
			} else {
				tempString << "\"right\" : { \"VertexCount\" : ";
			}
			tempString << meshData[j]->VertexCount;
			tempString << ", \"IndexCount\" : " << meshData[j]->IndexCount << ", ";
			
			tempString << "\"ScreenPosNDC\" : [";
			for ( i = 0; i < meshData[j]->VertexCount; ++i ) {
				tempString << meshData[j]->pVertexData[i].ScreenPosNDC.x << ",";
				tempString << meshData[j]->pVertexData[i].ScreenPosNDC.y;
				if ( i != meshData[j]->VertexCount-1 ) tempString << ",";
			}
			
			tempString << "], \"TimeWarpFactor\" : [";
			for ( i = 0; i < meshData[j]->VertexCount; ++i ) {
				tempString << meshData[j]->pVertexData[i].TimeWarpFactor;
				if ( i != meshData[j]->VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"VignetteFactor\" : [";
			for ( i = 0; i < meshData[j]->VertexCount; ++i ) {
				tempString << meshData[j]->pVertexData[i].VignetteFactor;
				if ( i != meshData[j]->VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"TanEyeAnglesR\" : [";
			for ( i = 0; i < meshData[j]->VertexCount; ++i ) {
				tempString << meshData[j]->pVertexData[i].TanEyeAnglesR.x << ",";
				tempString << meshData[j]->pVertexData[i].TanEyeAnglesR.y;
				if ( i != meshData[j]->VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"TanEyeAnglesG\" : [";
			for ( i = 0; i < meshData[j]->VertexCount; ++i ) {
				tempString << meshData[j]->pVertexData[i].TanEyeAnglesG.x << ",";
				tempString << meshData[j]->pVertexData[i].TanEyeAnglesG.y;
				if ( i != meshData[j]->VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"TanEyeAnglesB\" : [";
			for ( i = 0; i < meshData[j]->VertexCount; ++i ) {
				tempString << meshData[j]->pVertexData[i].TanEyeAnglesB.x << ",";
				tempString << meshData[j]->pVertexData[i].TanEyeAnglesB.y;
				if ( i != meshData[j]->VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"pIndexData\" : [";
			for ( i = 0; i < meshData[j]->IndexCount; ++i ) {
				tempString << meshData[j]->pIndexData[i];
				if ( i != meshData[j]->IndexCount-1 ) tempString << ",";
			}
			
			tempString << "] }";
			if ( j == 0 ) {
				tempString << ",\n";
			}
		}
		
		tempString << "\n}";

		std::ofstream myfile;
		myfile.open ("mesh.txt", std::fstream::out | std::fstream::trunc);
		myfile << tempString.str();
		myfile.close();
		
		return tempString.str();
	}
} //namespace ozo