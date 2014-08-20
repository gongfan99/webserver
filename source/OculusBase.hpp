#ifndef __OCULUSBASE_HPP__
#define __OCULUSBASE_HPP__

#include "OVR_CAPI.h"

namespace ozo {

class OculusBase {
public:
	//all are external output interfaces
	ovrHmdDesc* hmd;
	ovrEyeRenderDesc RenderDesc[2];
	ovrDistortionMesh meshData[2];
	ovrTrackingState* data; 

	OculusBase() {}; 
	~OculusBase() {};	
};

} //namespace ozo

#endif // __OCULUSBASE_HPP__