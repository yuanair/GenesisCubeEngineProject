//
// Created by admin on 2023/12/27.
//

#pragma once

#include "TUnknown.h"
#include "GD2D1HwndRenderTarget.h"
#include "../Game/GWindow.h"

namespace GenesisCube
{
	///
	/// D2D工厂
	///
	class GD2D1Factory : public TUnknown<ID2D1Factory1>
	{
	public:
		
		///
		/// 创建
		/// \return FResult
		[[nodiscard]]
		static FResult Create(ID2D1Factory1 **factory);
		
		///
		/// 创建渲染目标
		/// \param renderTarget 渲染目标
		/// \param window 窗口
		/// \return FResult
		[[nodiscard]]
		FResult CreateHwndRenderTarget(GD2D1HwndRenderTarget &renderTarget, const GWindow &window);
		
		
	};
	
} // GenesisCube
