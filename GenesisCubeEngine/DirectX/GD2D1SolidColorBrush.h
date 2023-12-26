//
// Created by admin on 2023/12/27.
//

#pragma once

#include "TUnknown.h"

namespace GenesisCubeEngine
{
	///
	/// D2D纯色笔刷
	///
	class GD2D1SolidColorBrush : public TUnknown<ID2D1SolidColorBrush>
	{
	public:
		
		///
		/// 设置颜色
		/// \param r 红
		/// \param g 绿
		/// \param b 蓝
		/// \param a 透明度
		/// \return HRESULT
		void SetColor(float r, float g, float b, float a = 1.0f);
		
		///
		/// 设置颜色
		/// \param color 颜色
		/// \return HRESULT
		void SetColor(const D2D1_COLOR_F &color);
		
		///
		/// \return 颜色
		D2D1_COLOR_F GetColor();
		
	};
	
} // GenesisCubeEngine
