//
// Created by admin on 2023/12/27.
//

#pragma once

#include "TUnknown.h"

namespace GenesisCube
{
	///
	/// DXGI设备
	///
	class GDXGIDevice : public TUnknown<IDXGIDevice1>
	{
	public:
		
		///
		/// 创建
		/// \return HRESULT
		[[nodiscard]]
		FResult Create();
		
	};
	
} // GenesisCube
