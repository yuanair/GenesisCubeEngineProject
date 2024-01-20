//
// Created by admin on 2024/1/19.
//

#pragma once

#include "UUI.h"

namespace GenesisCube
{
	///
	/// 椭圆（圆）
	class UEllipse : public UUI
	{
	protected:
		
		void OnRender(RenderTarget *renderTarget) override;
	
	public:
		
		///
		/// 椭圆
		D2D1_ELLIPSE ellipse{{10.0f, 10.0f}, 10.0f, 10.0f};
		
		///
		/// 填充笔刷
		TComPtr<Brush> fillBrush;
		
		///
		/// 边框笔刷
		TComPtr<Brush> drawBrush;
		
	};
	
} // GenesisCube
