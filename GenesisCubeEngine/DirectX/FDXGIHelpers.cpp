//
// Created by admin on 2024/1/19.
//

#include "FDXGIHelpers.h"

namespace GenesisCube
{
	HRESULT FDXGIHelpers::CreateDevice(TComPtr <IDXGIDevice1> &device)
	{
		return ::CreateDXGIFactory1(IID_PPV_ARGS(device.ReleaseAndGetAddressOf()));
	}
} // GenesisCube