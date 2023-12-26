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
	
	void GD2D1HwndRenderTarget::DrawRectangle(const D2D1_RECT_F &rect, const GD2D1SolidColorBrush &brush, float width)
	{
		this->ptr->DrawRectangle(rect, brush.Get(), width);
	}
	
	void GD2D1HwndRenderTarget::FillRectangle(const D2D1_RECT_F &rect, const GD2D1SolidColorBrush &brush)
	{
		this->ptr->FillRectangle(rect, brush.Get());
	}
} // GenesisCubeEngine