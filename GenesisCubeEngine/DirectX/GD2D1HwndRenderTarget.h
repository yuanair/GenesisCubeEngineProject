//
// Created by admin on 2023/12/27.
//

#pragma once

#include "TUnknown.h"
#include "GD2D1SolidColorBrush.h"
#include "GD2D1BitmapBrush.h"
#include "GDWriteFactory.h"
#include "GD2D1Bitmap.h"
#include "../IO/FImageData.h"

namespace GenesisCube
{
	///
	/// D2D渲染目标
	///
	class GD2D1HwndRenderTarget : public TUnknown<ID2D1HwndRenderTarget>
	{
	public:
		
		///
		/// 创建
		/// \param brush 笔刷
		/// \param color 颜色
		/// \return FResult
		[[nodiscard]]
		FResult CreateSolidBrush(GD2D1SolidColorBrush &brush, const D2D1_COLOR_F &color);
		
		///
		/// 创建
		/// \param bitmap 目标图片
		/// \param size 大小
		/// \param pixelFormat 像素格式
		/// \return FResult
		[[nodiscard]]
		FResult CreateBitmap(GD2D1Bitmap &bitmap, const D2D1_SIZE_U &size,
							 DXGI_FORMAT pixelFormat = DXGI_FORMAT_R8G8B8A8_UNORM);
		
		///
		/// 创建
		/// \param bitmap 目标图片
		/// \param srcData 数据
		/// \param pitch 数据大小
		/// \param size 大小
		/// \return FResult
		[[nodiscard]]
		FResult CreateBitmap(GD2D1Bitmap &bitmap, const void *srcData, uint32_t pitch, const D2D1_SIZE_U &size);
		
		///
		/// 从文件加载图片
		/// \param bitmap 目标图片
		/// \param data 图片数据
		/// \return FResult
		[[nodiscard]]
		FResult CreateBitmapFromImageData(GD2D1Bitmap &bitmap, const FImageData &data);
		
		///
		/// 创建画笔
		/// \param brush 目标
		/// \param bitmap 图片
		/// \return FResult
		[[nodiscard]]
		FResult CreateBitmapBrush(GD2D1BitmapBrush &brush, ID2D1Bitmap *bitmap);
		
		///
		/// 开始渲染
		///
		void BeginDraw();
		
		///
		/// 清空屏幕
		/// \param color 颜色
		void Clear(const D2D1_COLOR_F &color);
		
		///
		/// 大小更改
		/// \param width 宽度
		/// \param height 高度
		/// \return FResult
		[[nodiscard]]
		FResult Resize(uint32_t width, uint32_t height);
		
		///
		/// 显示线段
		/// \param point0 端点0
		/// \param point1 端点1
		/// \param brush 笔刷
		/// \param width 宽度
		void DrawLine(const D2D1_POINT_2F &point0, const D2D1_POINT_2F &point1, const GD2D1Brush &brush,
					  float width = 1.0f);
		
		///
		/// 显示文字
		/// \param text 文字
		/// \param textFormat 字体样式
		/// \param rect 显示范围
		/// \param brush 笔刷
		void DrawText(const TString &text, const GDWriteTextFormat &textFormat, const D2D1_RECT_F &rect,
					  const GD2D1Brush &brush);
		
		///
		/// 显示矩形框
		/// \param rect 矩形
		/// \param brush 笔刷
		/// \param width 宽度
		void DrawRectangle(const D2D1_RECT_F &rect, const GD2D1Brush &brush, float width = 1.0f);
		
		///
		/// 显示矩形
		/// \param rect 矩形
		/// \param brush 笔刷
		void FillRectangle(const D2D1_RECT_F &rect, const GD2D1Brush &brush);
		
		///
		/// 显示圆形框
		/// \param point 圆心位置
		/// \param r 半径
		/// \param brush 笔刷
		/// \param width 宽度
		void DrawCircle(const D2D1_POINT_2F &point, float r, const GD2D1Brush &brush, float width = 1.0f);
		
		///
		/// 显示圆形
		/// \param point 圆心位置
		/// \param r 半径
		/// \param brush 笔刷
		void FillCircle(const D2D1_POINT_2F &point, float r, const GD2D1Brush &brush);
		
		///
		/// 结束渲染
		/// \return FResult
		[[nodiscard]]
		FResult EndDraw();
		
	};
	
} // GenesisCube
