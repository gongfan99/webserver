#ifndef __DIRECTCAMERA_HPP__
#define __DIRECTCAMERA_HPP__

#include "SourceBase.hpp"
#include "Adapter.hpp"
#include "ImageProduceCamera.h"

namespace ozo {

class DirectCamera : public SourceBase{
public:
	DirectCamera();
	~DirectCamera();
	void process();
private:
	AdapterDirect* adapter;
	ImageProduceCamera* camera;
};

} //namespace ozo

#endif // __DIRECTCAMERA_HPP__