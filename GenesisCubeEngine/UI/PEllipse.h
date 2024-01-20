//
// Created by admin on 2024/1/19.
//

#pragma once

#include "UUI.h"

namespace GenesisCube
{
	///
	/// 椭圆（圆）面板
	class PEllipse : public PPanel
	{
	protected:
		
		void OnRender(RenderTarget *renderTarget) override;
	
	public:
		
		///
		/// 填充笔刷
		TComPtr<Brush> fillBrush;
		
		///
		/// 边框笔刷
		TComPtr<Brush> drawBrush;
		
	};
	
} // GenesisCube
