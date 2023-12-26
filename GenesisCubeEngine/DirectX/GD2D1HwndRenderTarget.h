//
// Created by admin on 2023/12/27.
//

#pragma once

#include "TUnknown.h"
#include "GD2DFactory.h"
#include "GD2D1SolidColorBrush.h"
#include "GD2D1BitmapBrush.h"
#include "GDWriteFactory.h"
#include "GD2D1Bitmap.h"
#include "../Game/GWindow.h"

namespace GenesisCubeEngine
{
	///
	/// D2D渲染目标
	///
	class GD2D1HwndRenderTarget : public TUnknown<ID2D1HwndRenderTarget>
	{
	public:
		
		///
		/// 创建
		/// \param factory 工厂
		/// \param window 窗口
		/// \return HRESULT
		[[nodiscard]]
		HRESULT Create(const GD2DFactory &factory, const GWindow &window);
		
		///
		/// 创建
		/// \param brush 笔刷
		/// \param color 颜色
		/// \return HRESULT
		[[nodiscard]]
		HRESULT CreateSolidBrush(GD2D1SolidColorBrush &brush, const D2D1_COLOR_F &color);
		
		///
		/// 创建
		/// \param bitmap 目标图片
		/// \param size 大小
		/// \return HRESULT
		[[nodiscard]]
		HRESULT CreateBitmap(GD2D1Bitmap &bitmap, const D2D1_SIZE_U &size);
		
		///
		/// 创建
		/// \param bitmap 目标图片
		/// \param srcData 数据
		/// \param pitch 数据大小
		/// \param size 大小
		/// \return HRESULT
		[[nodiscard]]
		HRESULT CreateBitmap(GD2D1Bitmap &bitmap, const void *srcData, uint32_t pitch, const D2D1_SIZE_U &size);
		
		///
		/// 创建画笔
		/// \param brush 目标
		/// \param bitmap 图片
		/// \return HRESULT
		[[nodiscard]]
		HRESULT CreateBitmapBrush(GD2D1BitmapBrush &brush, const GD2D1Bitmap &bitmap);
		
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
		/// \return HRESULT
		[[nodiscard]]
		HRESULT Resize(uint32_t width, uint32_t height);
		
		///
		/// 显示线段
		/// \param point0 端点0
		/// \param point1 端点1
		/// \param brush 笔刷
		/// \param width 宽度
		void DrawLine(const D2D1_POINT_2F &point0, const D2D1_POINT_2F &point1, const GD2D1SolidColorBrush &brush,
					  float width = 1.0f);
		
		///
		/// 显示文字
		/// \param text 文字
		/// \param textFormat 字体样式
		/// \param rect 显示范围
		/// \param brush 笔刷
		void DrawText(const TString &text, const GDWriteTextFormat &textFormat, const D2D1_RECT_F &rect,
					  const GD2D1SolidColorBrush &brush);
		
		///
		/// 显示矩形框
		/// \param rect 矩形
		/// \param brush 笔刷
		/// \param width 宽度
		void DrawRectangle(const D2D1_RECT_F &rect, ID2D1Brush *brush, float width = 1.0f);
		
		///
		/// 显示矩形
		/// \param rect 矩形
		/// \param brush 笔刷
		void FillRectangle(const D2D1_RECT_F &rect, ID2D1Brush *brush);
		
		///
		/// 显示圆形框
		/// \param point 圆心位置
		/// \param r 半径
		/// \param brush 笔刷
		/// \param width 宽度
		void DrawCircle(const D2D1_POINT_2F &point, float r, const GD2D1SolidColorBrush &brush, float width = 1.0f);
		
		///
		/// 显示圆形
		/// \param point 圆心位置
		/// \param r 半径
		/// \param brush 笔刷
		void FillCircle(const D2D1_POINT_2F &point, float r, const GD2D1SolidColorBrush &brush);
		
		///
		/// 结束渲染
		/// \return HRESULT
		[[nodiscard]]
		HRESULT EndDraw();
		
	};
	
} // GenesisCubeEngine
