//
// Created by admin on 2023/12/27.
//

#include "GDXGIDevice.h"

namespace GenesisCubeEngine
{
	HRESULT GDXGIDevice::Create()
	{
		return CreateDXGIFactory1(IID_PPV_ARGS(&this->ptr));
	}
} // GenesisCubeEngine