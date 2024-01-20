//
// Created by admin on 2024/1/19.
//

#pragma once

#include "../Core/Header.h"
#include "../../GenesisCubeBase/Core/TPtr.h"

namespace GenesisCube
{
	
	///
	/// DXGI帮助类
	class FDXGIHelpers
	{
	public:
		
		///
		/// \param device 设备
		/// \return
		static HRESULT CreateDevice(TComPtr<IDXGIDevice1> &device);
		
	};
	
} // GenesisCube
