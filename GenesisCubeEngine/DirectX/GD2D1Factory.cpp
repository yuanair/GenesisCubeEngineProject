//
// Created by admin on 2023/12/27.
//

#include "GD2D1Factory.h"

namespace GenesisCube
{
	FResult GD2D1Factory::Create(ID2D1Factory1 **factory)
	{
		
		D2D1_FACTORY_OPTIONS options
			{
				.debugLevel = D2D1_DEBUG_LEVEL_ERROR
			};
		
		return D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(ID2D1Factory1),
			&options,
			reinterpret_cast<void **>(factory)
		);
	}
	
	FResult GD2D1Factory::CreateHwndRenderTarget(GD2D1HwndRenderTarget &renderTarget, const GWindow &window)
	{
		ThrowIfNull();
		return GetComPtr()->CreateHwndRenderTarget
			(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(
					window.GetHWnd(),
					D2D1::SizeU(window.GetWindowRect().width, window.GetWindowRect().height)
				),
				renderTarget.ReleaseAndGetAddressOf()
			);;
	}
} // GenesisCube