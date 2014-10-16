#ifndef __OZO_OCULUSDK2_HPP__
#define __OZO_OCULUSDK2_HPP__

#include "OVR_CAPI.h"
#include "utils.hpp"

namespace ozo {

class OculusDK2 {
public:
	//external output interface
	OculusInterface OcuInf;

	OculusDK2();
	~OculusDK2();
	inline void process(){
		OcuInf.trackingState = ovrHmd_GetTrackingState(OcuInf.hmd, ovr_GetTimeInSeconds());
/* 		//time warp is not used; so timeWarpMatrices are all identity matrix.
		int eyeNum;
		ovrPosef eyeRenderPose[2];
		for ( eyeNum = 0; eyeNum < 2; eyeNum++ ) {
			eyeRenderPose[eyeNum] = trackingState.HeadPose.ThePose;
			ovrHmd_GetEyeTimewarpMatrices(hmd, (ovrEyeType)eyeNum, eyeRenderPose[eyeNum], timeWarpMatrices[eyeNum]);
		} */
	};
};

} //namespace ozo

#endif // __OZO_OCULUSDK2_HPP__