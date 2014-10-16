#include <iostream>
#include <fstream>
#include "OculusDK2.hpp"

using namespace ozo;

int main()
{
	OculusDK2 oculus;
	std::cout << "Product Name: " << (oculus.OcuInf.hmd)->ProductName << std::endl;
	std::cout << "Mesh data VertexCount: " << oculus.OcuInf.meshData[0].VertexCount << ", " << oculus.OcuInf.meshData[1].VertexCount << std::endl;
	std::cout << "Mesh data IndexCount: " << oculus.OcuInf.meshData[0].IndexCount << ", " << oculus.OcuInf.meshData[1].IndexCount << std::endl;

	std::ofstream myfile ("example.txt");
	if (myfile.is_open()) {
		for (int i=0; i<oculus.OcuInf.meshData[0].IndexCount; ++i) {
			myfile << oculus.OcuInf.meshData[0].pIndexData[i] << std::endl;
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
  
	oculus.process();
	ovrQuatf quat = oculus.OcuInf.trackingState.HeadPose.ThePose.Orientation;
	std::cout << "Quaternion: " << quat.w << quat.x << quat.y << quat.z << std::endl;
}