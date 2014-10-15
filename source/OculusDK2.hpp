#ifndef __OZO_OCULUSDK2_HPP__
#define __OZO_OCULUSDK2_HPP__

#include "OVR_CAPI.h"

namespace ozo {

class OculusDK2 {
public:
	//all are external output interfaces
	ovrHmdDesc* hmd;
	ovrEyeRenderDesc EyeRenderDesc[2];
	ovrDistortionMesh meshData[2];
	Sizei RenderTargetSize[2];
	ovrVector2f UVScaleOffset[2][2];
	ovrMatrix4f timeWarpMatrices[2][2];
	ovrTrackingState trackingState;
	OculusDK2();
	~OculusDK2();
	inline void process(){
		int eyeNum;
		ovrPosef eyeRenderPose[2];
		trackingState = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
		for ( eyeNum = 0; eyeNum < 2; eyeNum++ ) {
			eyeRenderPose[eyeNum] = trackingState.HeadPose.ThePose;
			ovrHmd_GetEyeTimewarpMatrices(hmd, (ovrEyeType)eyeNum, eyeRenderPose[eyeNum], timeWarpMatrices[eyeNum]);
		}
	};
};

} //namespace ozo

#endif // __OZO_OCULUSDK2_HPP__