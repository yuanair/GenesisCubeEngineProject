//
// Created by admin on 2023/12/27.
//

#pragma once

#include "TUnknown.h"

namespace GenesisCubeEngine
{
	///
	/// D2D工厂
	///
	class GD2DFactory : public TUnknown<ID2D1Factory1>
	{
	public:
		
		///
		/// 创建
		/// \return HRESULT
		[[nodiscard]]
		HRESULT Create();
		
	};
	
} // GenesisCubeEngine
