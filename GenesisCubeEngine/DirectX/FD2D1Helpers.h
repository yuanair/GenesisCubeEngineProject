//
// Created by admin on 2024/1/19.
//

#pragma once

#include "../Core/Header.h"
#include "../IO/FImageData.h"

#include "../../GenesisCubeBase/Core/TPtr.h"
#include "../../GenesisCubeBase/Win32/Window.h"

namespace GenesisCube
{
	///
	/// D2D1帮助类
	class FD2D1Helpers
	{
	public:
		
		///
		/// 创建工厂
		/// \param factory D2D1工厂
		/// \return
		static HRESULT CreateFactory(TComPtr<ID2D1Factory1> &factory);
		
		///
		/// 创建窗口渲染目标
		/// \param renderTarget 渲染目标
		/// \param factory 工厂
		/// \param window 窗口
		/// \return
		static HRESULT CreateHwndRenderTarget(
			TComPtr<ID2D1HwndRenderTarget> &renderTarget, TComPtr<ID2D1Factory1> &factory, const Win32::FWindow &window
		);
		
		///
		/// 创建位图
		/// \param renderTarget 渲染目标
		/// \param bitmap 位图
		/// \param data 数据
		/// \param format 格式
		/// \return
		static HRESULT CreateBitmapFromImageData(
			ID2D1RenderTarget *renderTarget, TComPtr<ID2D1Bitmap> &bitmap, const FImageData &data,
			D2D1_PIXEL_FORMAT format);
		
		///
		/// 画字符串
		/// \param renderTarget 渲染目标
		/// \param str 字符串
		/// \param textFormat 格式
		/// \param layoutRect 矩形
		/// \param defaultFillBrush 填充笔刷
		static void DrawString(
			ID2D1RenderTarget *renderTarget, const TString &str, TComPtr<IDWriteTextFormat> &textFormat,
			D2D1_RECT_F &layoutRect, ID2D1Brush *defaultFillBrush
		);
	};
} // GenesisCube
