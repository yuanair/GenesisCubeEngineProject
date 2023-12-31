//
// Created by admin on 2023/12/28.
//

#pragma once

#include "GUI.h"

namespace GenesisCube
{
	///
	/// UI盒子
	///
	class GBox : public GUI
	{
	public:
		
		void OnRender(ID2D1RenderTarget *renderTarget) override;
		
		bool IsOnUI(const D2D1_POINT_2F &point) override;
	
	public:
		
		[[nodiscard]]
		GBox *Clone() const noexcept override;
		
		GCLASS_BODY(GBox)
	
	public:
		
		///
		/// 背景笔刷
		///
		GD2D1Brush brush;
		
	};
	
} // GenesisCube
