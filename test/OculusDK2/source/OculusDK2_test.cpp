#include <iostream>
#include "OculusDK2.hpp"

using namespace ozo;

int main()
{
	OculusDK2 *oculus = new OculusDK2;
	std::cout << "Product Name: " << oculus->hmd->ProductName << std::endl;

	oculus->process();
	ovrQuatf quat = oculus->data->HeadPose.ThePose.Orientation;
	std::cout << "Quaternion: " << quat.x << std::endl;
	
	delete oculus;
}