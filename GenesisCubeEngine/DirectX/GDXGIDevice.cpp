//
// Created by admin on 2023/12/27.
//

#include "GDXGIDevice.h"

namespace GenesisCube
{
	FResult GDXGIDevice::Create()
	{
		return CreateDXGIFactory1(IID_PPV_ARGS(&GetComPtr()));
	}
} // GenesisCube