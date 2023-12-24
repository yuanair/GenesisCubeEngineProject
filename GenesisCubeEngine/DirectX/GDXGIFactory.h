//
// Created by admin on 2023/12/25.
//

#pragma once

#include "TUnknown.h"
#include "GDXGISwapChain.h"

#include "../Game/GWindow.h"

namespace GenesisCubeEngine
{
	///
	/// DXGI工厂
	///
	class GDXGIFactory : public TUnknown<IDXGIFactory2>
	{
	public:
		
		///
		/// 创建交换链
		/// \param swapChain 交换链
		/// \param device 设备
		/// \param window 窗口
		/// \param bufferCount 缓冲区数量
		/// \return HRESULT
		HRESULT CreateSwapChain(GDXGISwapChain &swapChain, const class GDevice &device, const GWindow &window,
								uint32_t bufferCount = 2);
		
	};
	
} // GenesisCubeEngine
