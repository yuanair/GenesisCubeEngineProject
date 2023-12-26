//
// Created by admin on 2023/12/27.
//

#pragma once

#include "TUnknown.h"
#include "GD2DFactory.h"

namespace GenesisCubeEngine
{
	
	///
	/// D2D设备
	///
	class GD2D1Device : public TUnknown<ID2D1Device>
	{
	public:
		
		///
		/// 创建
		/// \param factory 工厂
		/// \return HRESULT
		[[nodiscard]]
		HRESULT Create(const GD2DFactory &factory);
		
	};
	
} // GenesisCubeEngine
