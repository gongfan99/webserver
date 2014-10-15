#include "OculusDK2.hpp"
#include <iostream>

namespace ozo {

OculusDK2::OculusDK2() {
    ovr_Initialize();
	hmd = (ovrHmdDesc*)ovrHmd_Create(0);
    if (!hmd) hmd = (ovrHmdDesc*)ovrHmd_CreateDebug(ovrHmd_DK2); //create a virtual helmet if a real one cannot be found.
	if (hmd->ProductName[0] == '\0') 
        std::cout << "Rift detected, display not enabled." << std::endl;

	ovrFovPort eyeFov[2] = { hmd->DefaultEyeFov[0], hmd->DefaultEyeFov[1] };

	int eyeNum;
	ovrRecti EyeRenderViewport;
	for ( eyeNum = 0; eyeNum < 2; eyeNum++ ) {
		RenderTargetSize[eyeNum] = ovrHmd_GetFovTextureSize(hmd, (ovrEyeType)eyeNum, eyeFov[eyeNum], 1.0f);
		
		EyeRenderDesc[eyeNum] = ovrHmd_GetRenderDesc(hmd, (ovrEyeType)eyeNum, eyeFov[eyeNum]);
		
		ovrHmd_CreateDistortionMesh(hmd, (ovrEyeType)eyeNum, eyeFov[eyeNum], ovrDistortionCap_Chromatic | ovrDistortionCap_TimeWarp, &(meshData[eyeNum]));

		EyeRenderViewport.Pos =  Vector2i(0,0);
		EyeRenderViewport.Size =  Sizei(RenderTargetSize.w, RenderTargetSize.h);
		ovrHmd_GetRenderScaleAndOffset(eyeFov[eyeNum], RenderTargetSize[eyeNum], EyeRenderViewport, UVScaleOffset[eyeNum]);
	}

    ovrHmd_SetEnabledCaps(hmd, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

	// Start the sensor which informs of the Rift's pose and motion
    ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0);
}

OculusDK2::~OculusDK2() {
	int eyeNum;
	for ( eyeNum = 0; eyeNum < 2; eyeNum++ ) {
		ovrHmd_DestroyDistortionMesh( &(meshData[eyeNum]) );
	}
	
	ovrHmd_Destroy(hmd);
	ovr_Shutdown();
}

} //namespace ozo