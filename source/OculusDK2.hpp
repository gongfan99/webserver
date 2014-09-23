#ifndef __OZO_OCULUSDK2_HPP__
#define __OZO_OCULUSDK2_HPP__

#include "OVR_CAPI.h"

namespace ozo {

class OculusDK2 {
public:
	//all are external output interfaces
	ovrHmdDesc* hmd;
	ovrEyeRenderDesc RenderDesc[2];
	ovrDistortionMesh meshData[2];
	ovrTrackingState data;
	OculusDK2();
	~OculusDK2();
	inline void process(){
		data = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
	};
};

} //namespace ozo

#endif // __OZO_OCULUSDK2_HPP__