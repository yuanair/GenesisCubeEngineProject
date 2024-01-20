//
// Created by admin on 2024/1/19.
//

#include "FD2D1Helpers.h"

namespace GenesisCube
{
	HRESULT FD2D1Helpers::CreateFactory(TComPtr<ID2D1Factory1> &factory)
	{
		D2D1_FACTORY_OPTIONS options
			{
				.debugLevel = D2D1_DEBUG_LEVEL_ERROR
			};
		
		return D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(ID2D1Factory1),
			&options,
			reinterpret_cast<void **>(factory.ReleaseAndGetAddressOf())
		);
	}
	
	HRESULT FD2D1Helpers::CreateHwndRenderTarget(
		TComPtr<ID2D1HwndRenderTarget> &renderTarget, TComPtr<ID2D1Factory1> &factory, const Win32::FWindow &window)
	{
		return factory->CreateHwndRenderTarget
			(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(
					(HWND) window.GetHWnd(),
					D2D1::SizeU(window.GetClientRect().width, window.GetClientRect().height)
				),
				renderTarget.ReleaseAndGetAddressOf()
			);
	}
	
	HRESULT FD2D1Helpers::CreateBitmapFromImageData(ID2D1RenderTarget *renderTarget, TComPtr<ID2D1Bitmap> &bitmap,
													const FImageData &data, D2D1_PIXEL_FORMAT format)
	{
		return renderTarget->CreateBitmap(
			D2D1::SizeU(data.GetWidth(), data.GetHeight()),
			data.GetData(), data.GetWidth() * data.GetN(),
			D2D1::BitmapProperties(format), bitmap.ReleaseAndGetAddressOf()
		);
		
	}
	
	void FD2D1Helpers::DrawString(ID2D1RenderTarget *renderTarget, const TString &str,
								  TComPtr<IDWriteTextFormat> &textFormat, D2D1_RECT_F &layoutRect,
								  ID2D1Brush *defaultFillBrush)
	{
		renderTarget->DrawText(
			str.c_str(), (uint32_t) str.size(), textFormat.Get(), layoutRect, defaultFillBrush
		);
	}
} // GenesisCube