//
// Created by admin on 2023/12/27.
//

#include "GD2D1HwndRenderTarget.h"

namespace GenesisCubeEngine
{
	HRESULT GD2D1HwndRenderTarget::Create(const GD2DFactory &factory, const GWindow &window)
	{
		return factory.Get()->CreateHwndRenderTarget
			(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(
					window.GetHWnd(),
					D2D1::SizeU(window.GetWindowRect().width, window.GetWindowRect().height)
				),
				this->ptr.ReleaseAndGetAddressOf()
			);
	}
	
	void GD2D1HwndRenderTarget::BeginDraw()
	{
		this->ptr->BeginDraw();
	}
	
	HRESULT GD2D1HwndRenderTarget::EndDraw()
	{
		return this->ptr->EndDraw();
	}
	
	void GD2D1HwndRenderTarget::Clear(const D2D1_COLOR_F &color)
	{
		this->ptr->Clear(color);
	}
	
	HRESULT GD2D1HwndRenderTarget::CreateSolidBrush(GD2D1SolidColorBrush &brush, const D2D1_COLOR_F &color)
	{
		return this->ptr->CreateSolidColorBrush(color, brush.ReleaseAndGetAddressOf());
	}
	
	void
	GD2D1HwndRenderTarget::DrawText(const TString &text, const GDWriteTextFormat &textFormat, const D2D1_RECT_F &rect,
									const GD2D1SolidColorBrush &brush)
	{
		this->ptr->DrawText(text.c_str(), text.size(), textFormat.Get(), rect, brush.Get());
	}
	
	HRESULT GD2D1HwndRenderTarget::Resize(uint32_t width, uint32_t height)
	{
		return this->ptr->Resize(D2D1::SizeU(width, height));
	}
	
	void GD2D1HwndRenderTarget::DrawRectangle(const D2D1_RECT_F &rect, ID2D1Brush *brush, float width)
	{
		this->ptr->DrawRectangle(rect, brush, width);
	}
	
	void GD2D1HwndRenderTarget::FillRectangle(const D2D1_RECT_F &rect, ID2D1Brush *brush)
	{
		this->ptr->FillRectangle(rect, brush);
	}
	
	void GD2D1HwndRenderTarget::DrawCircle(const D2D1_POINT_2F &point, float r, const GD2D1SolidColorBrush &brush,
										   float width)
	{
		this->ptr->DrawEllipse(D2D1::Ellipse(point, r, r), brush.Get(), width);
	}
	
	void GD2D1HwndRenderTarget::FillCircle(const D2D1_POINT_2F &point, float r, const GD2D1SolidColorBrush &brush)
	{
		this->ptr->FillEllipse(D2D1::Ellipse(point, r, r), brush.Get());
	}
	
	void
	GD2D1HwndRenderTarget::DrawLine(const D2D1_POINT_2F &point0, const D2D1_POINT_2F &point1,
									const GD2D1SolidColorBrush &brush, float width)
	{
		this->ptr->DrawLine(point0, point1, brush.Get(), width);
	}
	
	HRESULT GD2D1HwndRenderTarget::CreateBitmap(GD2D1Bitmap &bitmap, const void *srcData, uint32_t pitch,
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
		return this->ptr->CreateBitmap(size, srcData, pitch, properties, bitmap.ReleaseAndGetAddressOf());
	}
	
	HRESULT GD2D1HwndRenderTarget::CreateBitmapBrush(GD2D1BitmapBrush &brush, const GD2D1Bitmap &bitmap)
	{
		return this->ptr->CreateBitmapBrush(bitmap.Get(), brush.ReleaseAndGetAddressOf());
	}
	
	HRESULT GD2D1HwndRenderTarget::CreateBitmap(GD2D1Bitmap &bitmap, const D2D1_SIZE_U &size)
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
		return this->ptr->CreateBitmap(size, properties, bitmap.ReleaseAndGetAddressOf());
	}
} // GenesisCubeEngine