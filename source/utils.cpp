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
	std::string OculusInitString(OculusInterface* OcuInf) {
		int i,j;
		std::ostringstream tempString;

		tempString << "{\n\"m\" : \"OculusInit\", \n";

		//send Oculus screen resolution
		tempString << "\"resolution\" : [" << OcuInf->hmd->Resolution.w << "," << OcuInf->hmd->Resolution.h << "],\n"; //end of resolution

		//send Oculus FOV
		tempString << "\"FOV\" : [";
		for ( i = 0; i < 2; ++i ) {
			tempString << OcuInf->EyeRenderDesc[i].Fov.UpTan << "," << OcuInf->EyeRenderDesc[i].Fov.DownTan << "," << OcuInf->EyeRenderDesc[i].Fov.LeftTan << "," << OcuInf->EyeRenderDesc[i].Fov.RightTan;
			if ( i == 0 ) {
				tempString << ",\n";
			}
		}
		tempString << "],\n"; //end of FOV

		//send Oculus distortion mesh
		ovrDistortionMesh* meshData = OcuInf->meshData;
		tempString << "\"meshData\" : {\n";
		for ( j = 0; j < 2; ++j ) {
			if ( j == 0 ) {
				tempString << "\"left\" : { \"VertexCount\" : ";
			} else {
				tempString << "\"right\" : { \"VertexCount\" : ";
			}
			tempString << meshData[j].VertexCount;
			tempString << ", \"IndexCount\" : " << meshData[j].IndexCount << ", ";
			
			tempString << "\"ScreenPosNDC\" : [";
			for ( i = 0; i < meshData[j].VertexCount; ++i ) {
				tempString << meshData[j].pVertexData[i].ScreenPosNDC.x << ",";
				tempString << meshData[j].pVertexData[i].ScreenPosNDC.y;
				if ( i != meshData[j].VertexCount-1 ) tempString << ",";
			}
			
			tempString << "], \"TimeWarpFactor\" : [";
			for ( i = 0; i < meshData[j].VertexCount; ++i ) {
				tempString << meshData[j].pVertexData[i].TimeWarpFactor;
				if ( i != meshData[j].VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"VignetteFactor\" : [";
			for ( i = 0; i < meshData[j].VertexCount; ++i ) {
				tempString << meshData[j].pVertexData[i].VignetteFactor;
				if ( i != meshData[j].VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"TanEyeAnglesR\" : [";
			for ( i = 0; i < meshData[j].VertexCount; ++i ) {
				tempString << meshData[j].pVertexData[i].TanEyeAnglesR.x << ",";
				tempString << meshData[j].pVertexData[i].TanEyeAnglesR.y;
				if ( i != meshData[j].VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"TanEyeAnglesG\" : [";
			for ( i = 0; i < meshData[j].VertexCount; ++i ) {
				tempString << meshData[j].pVertexData[i].TanEyeAnglesG.x << ",";
				tempString << meshData[j].pVertexData[i].TanEyeAnglesG.y;
				if ( i != meshData[j].VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"TanEyeAnglesB\" : [";
			for ( i = 0; i < meshData[j].VertexCount; ++i ) {
				tempString << meshData[j].pVertexData[i].TanEyeAnglesB.x << ",";
				tempString << meshData[j].pVertexData[i].TanEyeAnglesB.y;
				if ( i != meshData[j].VertexCount-1 ) tempString << ",";
			}

			tempString << "], \"pIndexData\" : [";
			for ( i = 0; i < meshData[j].IndexCount; ++i ) {
				tempString << meshData[j].pIndexData[i];
				if ( i != meshData[j].IndexCount-1 ) tempString << ",";
			}
			
			tempString << "] }";
			if ( j == 0 ) {
				tempString << ",\n";
			}
		}
		tempString << "\n}\n"; //end of distortion mesh

		//send Oculus RenderTargetSize
		tempString << "\"RenderTargetSize\" : [" << OcuInf->RenderTargetSize[0].w << "," << OcuInf->RenderTargetSize[0].h << ","  << OcuInf->RenderTargetSize[1].w << "," << OcuInf->RenderTargetSize[1].h << "],\n"; //end of RenderTargetSize

		//send Oculus UVScaleOffset
		tempString << "\"UVScaleOffset\" : [";
		for ( i = 0; i < 2; ++i ) {
			for ( j = 0; j < 2; ++j ) {
				tempString << OcuInf->UVScaleOffset[i][j].x << "," << OcuInf->UVScaleOffset[i][j].y;
				if ( i != 1 || j != 1 ) {
					tempString << ",";
				}
			}
		}
		tempString << "]\n"; //end of UVScaleOffset

		tempString << "\n}";

		std::ofstream myfile;
		myfile.open ("mesh.txt", std::fstream::out | std::fstream::trunc);
		myfile << tempString.str();
		myfile.close();

		return tempString.str();
	}

	std::string OculusUpdateString(OculusInterface* OcuInf) {
		int i, j, k, eyeNum;
		std::ostringstream tempString;

		tempString << "{\n\"m\" : \"OculusUpdate\", \n";

		//send Oculus timeWarpMatrices
		tempString << "\"timeWarpMatrices\" : [";
		for ( eyeNum = 0; eyeNum < 2; eyeNum++ ) {
			for ( i = 0; i < 2; i++ ) {
				for ( j = 0; j < 4; j++ ) {
					for ( k = 0; k < 4; k++ ) {
						tempString << OcuInf->timeWarpMatrices[eyeNum][i].M[j][k];
						if ( eyeNum != 1 || i != 1 || j != 3 || k != 3 ){
							tempString << ",";
						}
					}
				}
			}
		}
		tempString << "],\n";

		//send Oculus Orientation
		ovrQuatf &q = OcuInf->trackingState.HeadPose.ThePose.Orientation;
		tempString << "\"Orientation\" : [" << q.x << "," << q.y << "," << q.z << "," << q.w << "],\n";

		//send Oculus Position
		ovrVector3f &p = OcuInf->trackingState.HeadPose.ThePose.Position;
		tempString << "\"Orientation\" : [" << p.x << "," << p.y << "," << p.z << "]\n";

		tempString << "\n}";

		return tempString.str();
	}

} //namespace ozo