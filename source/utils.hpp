#ifndef __OZO_UTILS_HPP__
#define __OZO_UTILS_HPP__

#include <string>
#include <fstream>
#include <sstream>
#include <cmath> 
#include "OVR_CAPI.h"

namespace ozo
{
	typedef struct OculusInterface_	{
		ovrHmdDesc* hmd;
		ovrEyeRenderDesc EyeRenderDesc[2];
		ovrDistortionMesh meshData[2];
		ovrSizei RenderTargetSize[2];
		ovrVector2f UVScaleOffset[2][2];
		ovrMatrix4f timeWarpMatrices[2][2];
		ovrTrackingState trackingState;
	} OculusInterface;

    void sleep( unsigned int millisecs );

	std::string OculusInitString(OculusInterface* OcuInf);
	std::string OculusUpdateString(OculusInterface* OcuInf);

	template < typename T >
	std::string to_string( const T& n )	{
		std::ostringstream stm ;
		stm << n ;
		return stm.str() ;
	}
}

#endif // __OZO_UTILS_HPP__