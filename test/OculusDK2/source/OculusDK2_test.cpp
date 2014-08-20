#include <iostream>
#include "OculusDK2.h"

using namespace ozo;

int main()
{
	OculusDK2 oculus = new OculusDK2;
	std::cout << "Product Name: " << oculus->hmd->ProductName[0] << std::endl;

	oculus->process();
	ovrQuatf quat = oculus->data->HeadPose.ThePose.Orientation;
	std::cout << "Quaternion: " << quat << std::endl;
	
	delete oculus;
}