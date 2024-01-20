//
// Created by admin on 2024/1/19.
//

#pragma once

#include "UUI.h"

namespace GenesisCube
{
	///
	/// 文字
	class UText : public UUI
	{
	protected:
		
		void OnRender(RenderTarget *renderTarget) override;
	
	public:
		
		///
		/// 显示的文字
		TString showText;
		
		///
		/// 填充笔刷
		TComPtr<Brush> defaultFillBrush;
		
		///
		/// 填充笔刷
		TComPtr<TextFormat> textFormat;
		
		///
		/// 画文字设置
		D2D1_DRAW_TEXT_OPTIONS drawTextOptions = D2D1_DRAW_TEXT_OPTIONS_CLIP;
		
		///
		/// 测量模式
		DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL;
		
	};
	
} // GenesisCube
