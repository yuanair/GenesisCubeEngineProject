//
// Created by admin on 2023/12/25.
//

#pragma once

#include "TUnknown.h"
#include "Texture.h"

namespace GenesisCubeEngine
{
	///
	/// DXGI交换链
	///
	class GDXGISwapChain : public TUnknown<IDXGISwapChain1>
	{
	public:
		
		///
		/// 获取缓冲区
		/// \param texture 材质
		/// \param buffer
		/// \return HRESULT
		HRESULT GetBuffer(GTexture2D &texture, uint32_t buffer);
		
		///
		/// 交换缓冲区
		///
		/// \return
		HRESULT Present();
		
	};
	
} // GenesisCubeEngine
