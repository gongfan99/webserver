#ifndef __OCULUSDK2_HPP__
#define __OCULUSDK2_HPP__

#include "OculusBase.hpp"

namespace ozo {

class OculusDK2 : public OculusBase {
public:
	OculusDK2();
	~OculusDK2();
	inline void process();
};

} //namespace ozo

#endif // __OCULUSDK2_HPP__