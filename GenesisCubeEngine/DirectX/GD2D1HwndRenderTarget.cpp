//
// Created by admin on 2023/12/27.
//

#include "GD2D1HwndRenderTarget.h"

namespace GenesisCube
{
	
	void GD2D1HwndRenderTarget::BeginDraw()
	{
		GetComPtr()->BeginDraw();
	}
	
	FResult GD2D1HwndRenderTarget::EndDraw()
	{
		return GetComPtr()->EndDraw();
	}
	
	void GD2D1HwndRenderTarget::Clear(const D2D1_COLOR_F &color)
	{
		GetComPtr()->Clear(color);
	}
	
	FResult GD2D1HwndRenderTarget::CreateSolidBrush(GD2D1SolidColorBrush &brush, const D2D1_COLOR_F &color)
	{
		return GetComPtr()->CreateSolidColorBrush(color, brush.ReleaseAndGetAddressOf());
	}
	
	void
	GD2D1HwndRenderTarget::DrawText(const TString &text, const GDWriteTextFormat &textFormat, const D2D1_RECT_F &rect,
									const GD2D1Brush &brush)
	{
		GetComPtr()->DrawText(text.c_str(), (uint32_t) text.size(), textFormat.Get(), rect, brush.Get());
	}
	
	FResult GD2D1HwndRenderTarget::Resize(uint32_t width, uint32_t height)
	{
		return GetComPtr()->Resize(D2D1::SizeU(width, height));
	}
	
	void GD2D1HwndRenderTarget::DrawRectangle(const D2D1_RECT_F &rect, const GD2D1Brush &brush, float width)
	{
		GetComPtr()->DrawRectangle(rect, brush.Get(), width);
	}
	
	void GD2D1HwndRenderTarget::FillRectangle(const D2D1_RECT_F &rect, const GD2D1Brush &brush)
	{
		GetComPtr()->FillRectangle(rect, brush.Get());
	}
	
	void GD2D1HwndRenderTarget::DrawCircle(const D2D1_POINT_2F &point, float r, const GD2D1Brush &brush,
										   float width)
	{
		GetComPtr()->DrawEllipse(D2D1::Ellipse(point, r, r), brush.Get(), width);
	}
	
	void GD2D1HwndRenderTarget::FillCircle(const D2D1_POINT_2F &point, float r, const GD2D1Brush &brush)
	{
		GetComPtr()->FillEllipse(D2D1::Ellipse(point, r, r), brush.Get());
	}
	
	void
	GD2D1HwndRenderTarget::DrawLine(const D2D1_POINT_2F &point0, const D2D1_POINT_2F &point1,
									const GD2D1Brush &brush, float width)
	{
		GetComPtr()->DrawLine(point0, point1, brush.Get(), width);
	}
	
	FResult GD2D1HwndRenderTarget::CreateBitmap(GD2D1Bitmap &bitmap, const void *srcData, uint32_t pitch,
												const D2D1_SIZE_U &size)
	{
		D2D1_BITMAP_PROPERTIES properties
			{
				.pixelFormat =
					{
						.format=DXGI_FORMAT_R8G8B8A8_UNORM,
						.alphaMode=D2D1_ALPHA_MODE_IGNORE
					},
				.dpiX = 0.0f,
				.dpiY = 0.0f
			};
		return GetComPtr()->CreateBitmap(size, srcData, pitch, properties, bitmap.ReleaseAndGetAddressOf());
	}
	
	FResult GD2D1HwndRenderTarget::CreateBitmapBrush(GD2D1BitmapBrush &brush, ID2D1Bitmap *bitmap)
	{
		return GetComPtr()->CreateBitmapBrush(bitmap, brush.ReleaseAndGetAddressOf());
	}
	
	FResult GD2D1HwndRenderTarget::CreateBitmap(GD2D1Bitmap &bitmap, const D2D1_SIZE_U &size, DXGI_FORMAT pixelFormat)
	{
		D2D1_BITMAP_PROPERTIES properties
			{
				.pixelFormat =
					{
						.format=pixelFormat,
						.alphaMode=D2D1_ALPHA_MODE_IGNORE
					},
				.dpiX = 0.0f,
				.dpiY = 0.0f
			};
		return GetComPtr()->CreateBitmap(size, properties, bitmap.ReleaseAndGetAddressOf());
	}
	
	FResult GD2D1HwndRenderTarget::CreateBitmapFromImageData(GD2D1Bitmap &bitmap, const FImageData &data)
	{
		return CreateBitmap(bitmap, data.data, data.width * data.n, D2D1::SizeU(data.width, data.height));
	}
	
} // GenesisCube