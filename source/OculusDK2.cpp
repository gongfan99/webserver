#include "OculusDK2.hpp"

namespace ozo {

OculusDK2::OculusDK2() {
    ovr_Initialize();
	hmd = ovrHmd_Create(0);
    if (!hmd) hmd = ovrHmd_CreateDebug(ovrHmd_DK2); //create a virtual helmet if a real one cannot be found.
	if (hmd->ProductName[0] == '\0') 
        MessageBoxA(NULL,"Rift detected, display not enabled.","", MB_OK);

	ovrFovPort eyeFov[2] = { hmd->DefaultEyeFov[0], hmd->DefaultEyeFov[1] };

	int eyeNum;
	for ( eyeNum = 0; eyeNum < 2; eyeNum++ ) {
		EyeRenderDesc[eyeNum] = ovrHmd_GetRenderDesc(hmd, (ovrEyeType)eyeNum, eyeFov[eyeNum]);
		ovrHmd_CreateDistortionMesh(hmd, (ovrEyeType)eyeNum, eyeFov[eyeNum], ovrDistortionCap_Chromatic | ovrDistortionCap_TimeWarp, &(meshData[eyeNum]));
	}

    ovrHmd_SetEnabledCaps(hmd, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

	// Start the sensor which informs of the Rift's pose and motion
    ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0);

	data = new ovrTrackingState;
}

OculusDK2::~OculusDK2() {
	int eyeNum;
	for ( eyeNum = 0; eyeNum < 2; eyeNum++ ) {
		ovrHmd_DestroyDistortionMesh( &(meshData[eyeNum]) );
	}
	
	delete data;
	ovrHmd_Destroy(HMD);
	ovr_Shutdown();
}

inline void OculusDK2::process() {
	*data = ovrHmd_GetTrackingState(hmd, ovrGetTimeInSeconds());
}

} //namespace ozo