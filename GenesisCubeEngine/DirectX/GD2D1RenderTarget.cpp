//
// Created by admin on 2023/12/28.
//

#include "GD2D1RenderTarget.h"

namespace GenesisCube
{
	
	void GD2D1RenderTarget::BeginDraw()
	{
		GetComPtr()->BeginDraw();
	}
	
	void GD2D1RenderTarget::Clear(const D2D1_COLOR_F &color)
	{
		GetComPtr()->Clear(color);
	}
	
	void GD2D1RenderTarget::DrawLine(const D2D1_POINT_2F &point0, const D2D1_POINT_2F &point1, const GD2D1Brush &brush,
									 float width)
	{
		GetComPtr()->DrawLine(point0, point1, brush.Get(), width);
	}
	
	void GD2D1RenderTarget::DrawText(const TString &text, const GDWriteTextFormat &textFormat, const D2D1_RECT_F &rect,
									 const GD2D1Brush &brush)
	{
		GetComPtr()->DrawText(text.c_str(), (uint32_t) text.size(), textFormat.Get(), rect, brush.Get());
	}
	
	void GD2D1RenderTarget::DrawRectangle(const D2D1_RECT_F &rect, const GD2D1Brush &brush, float width)
	{
		GetComPtr()->DrawRectangle(rect, brush.Get(), width);
	}
	
	void GD2D1RenderTarget::FillRectangle(const D2D1_RECT_F &rect, const GD2D1Brush &brush)
	{
		GetComPtr()->FillRectangle(rect, brush.Get());
	}
	
	void GD2D1RenderTarget::DrawCircle(const D2D1_POINT_2F &point, float r, const GD2D1Brush &brush, float width)
	{
		GetComPtr()->DrawEllipse(D2D1::Ellipse(point, r, r), brush.Get(), width);
	}
	
	void GD2D1RenderTarget::FillCircle(const D2D1_POINT_2F &point, float r, const GD2D1Brush &brush)
	{
		GetComPtr()->FillEllipse(D2D1::Ellipse(point, r, r), brush.Get());
	}
	
	FResult GD2D1RenderTarget::EndDraw()
	{
		return GetComPtr()->EndDraw();
	}
} // GenesisCube