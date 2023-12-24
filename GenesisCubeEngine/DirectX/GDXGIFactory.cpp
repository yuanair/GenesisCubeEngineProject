//
// Created by admin on 2023/12/25.
//

#include "GDXGIFactory.h"
#include "GDevice.h"

namespace GenesisCubeEngine
{
	
	HRESULT GDXGIFactory::CreateSwapChain(GDXGISwapChain &swapChain, const GDevice &device, const GWindow &window,
										  uint32_t bufferCount)
	{
		if (!this->ptr) throw ENullptrException(__FUNCSIG__ TEXT(":: null factory"));
		DXGI_SWAP_CHAIN_DESC1 desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC1));
		auto rect = window.GetWindowRect();
		desc.Width = rect.width;
		desc.Height = rect.height;
		desc.BufferCount = bufferCount;
		desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		desc.Flags = window.IsWindowed() ? 0 : DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO;
		
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fd;
		fd.RefreshRate.Numerator = 60;
		fd.RefreshRate.Denominator = 1;
		fd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		fd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		fd.Windowed = window.IsWindowed();
		
		return this->ptr->CreateSwapChainForHwnd(
			device.Get(), window.GetHWnd(), &desc, &fd, nullptr, swapChain.ReleaseAndGetAddressOf());
	}
} // GenesisCubeEngine