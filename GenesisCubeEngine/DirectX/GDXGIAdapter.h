//
// Created by admin on 2023/12/25.
//

#pragma once

#include "TUnknown.h"

namespace GenesisCubeEngine
{
	///
	/// DXGI适配器
	///
	class GDXGIAdapter : public TUnknown<IDXGIAdapter>
	{
	public:
		
		GDXGIAdapter() = default;
		
		~GDXGIAdapter() override = default;
	
	public:
		
		///
		/// 获取
		///
		/// \param factory 工厂
		/// \return
		HRESULT GetParent(class GDXGIFactory &factory);
		
	};
	
} // GenesisCubeEngine
