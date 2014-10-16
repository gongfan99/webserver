#include "OculusDK2.hpp"
#include <iostream>

namespace ozo {

OculusDK2::OculusDK2() {
    ovr_Initialize();
	OcuInf.hmd = (ovrHmdDesc*)ovrHmd_Create(0);
    if (!OcuInf.hmd) OcuInf.hmd = (ovrHmdDesc*)ovrHmd_CreateDebug(ovrHmd_DK2); //create a virtual helmet if a real one cannot be found.
	if (OcuInf.hmd->ProductName[0] == '\0') 
        std::cout << "Rift detected, display not enabled." << std::endl;

	ovrFovPort eyeFov[2] = { OcuInf.hmd->DefaultEyeFov[0], OcuInf.hmd->DefaultEyeFov[1] };

	int eyeNum, i, j, k;
	ovrRecti EyeRenderViewport;
	for ( eyeNum = 0; eyeNum < 2; eyeNum++ ) {
		OcuInf.RenderTargetSize[eyeNum] = ovrHmd_GetFovTextureSize(OcuInf.hmd, (ovrEyeType)eyeNum, eyeFov[eyeNum], 1.0f);
		
		OcuInf.EyeRenderDesc[eyeNum] = ovrHmd_GetRenderDesc(OcuInf.hmd, (ovrEyeType)eyeNum, eyeFov[eyeNum]);
		
		ovrHmd_CreateDistortionMesh(OcuInf.hmd, (ovrEyeType)eyeNum, eyeFov[eyeNum], ovrDistortionCap_Chromatic | ovrDistortionCap_TimeWarp, &(OcuInf.meshData[eyeNum]));

		EyeRenderViewport.Pos.x = 0;
		EyeRenderViewport.Pos.y = 0;
		EyeRenderViewport.Size = OcuInf.RenderTargetSize[eyeNum];
		ovrHmd_GetRenderScaleAndOffset(eyeFov[eyeNum], OcuInf.RenderTargetSize[eyeNum], EyeRenderViewport, OcuInf.UVScaleOffset[eyeNum]);

		//initialize timeWarpMatrices to identity matrix
		for ( i = 0; i < 2; i++ ) {
			for ( j = 0; j < 4; j++ ) {
				for ( k = 0; k < 4; k++ ) {
					OcuInf.timeWarpMatrices[eyeNum][i].M[j][k] = (j==k)? 1 : 0;
				}
			}
		}
	}

    ovrHmd_SetEnabledCaps(OcuInf.hmd, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

	// Start the sensor which informs of the Rift's pose and motion
    ovrHmd_ConfigureTracking(OcuInf.hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0);
}

OculusDK2::~OculusDK2() {
	int eyeNum;
	for ( eyeNum = 0; eyeNum < 2; eyeNum++ ) {
		ovrHmd_DestroyDistortionMesh( &(OcuInf.meshData[eyeNum]) );
	}
	
	ovrHmd_Destroy(OcuInf.hmd);
	ovr_Shutdown();
}

} //namespace ozo