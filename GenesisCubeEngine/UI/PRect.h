//
// Created by admin on 2024/1/19.
//

#pragma once

#include "UUI.h"

namespace GenesisCube
{
	///
	/// 矩形面板
	class PRect : public PPanel
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
