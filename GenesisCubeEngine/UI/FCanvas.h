//
// Created by admin on 2024/1/19.
//

#pragma once

#include "UUI.h"
#include "PRect.h"

namespace GenesisCube
{
	///
	/// 画布
	class FCanvas
	{
	public:
		
		///
		/// 渲染
		void Render();
	
	public:
		
		///
		/// ui
		PRect ui;
		
		///
		/// 渲染目标
		TComPtr<ID2D1RenderTarget> renderTarget;
		
	};
	
} // GenesisCube
