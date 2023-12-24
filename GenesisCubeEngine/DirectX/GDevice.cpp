//
// Created by admin on 2023/12/24.
//

#include "GDevice.h"

namespace GenesisCubeEngine
{
	
	HRESULT GDevice::AutoCreate(GDeviceContext &deviceContext, GDXGIAdapter &adapter, GDXGIFactory &factory)
	{
		HRESULT hr = Create(deviceContext);
		if (FAILED(hr)) return hr;
		hr = GetAdapter(adapter);
		if (FAILED(hr)) return hr;
		hr = adapter.GetParent(factory);
		return hr;
	}
	
	HRESULT GDevice::Create(GDeviceContext &deviceContext)
	{
		D3D_FEATURE_LEVEL levels[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_11_1
		};
		
		// 此标志添加了对具有不同颜色通道顺序的表面的支持
		// 从API默认值中获取。它需要与Direct2D兼容。
		UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		
		// Debug
		if (bIsDebug) deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		
		
		// 创建Direct3D 11 API设备对象和相应的环境。
		GDevice device;
		GDeviceContext context;
		
		HRESULT hr = D3D11CreateDevice(
			nullptr,                    // 使用默认适配器。
			D3D_DRIVER_TYPE_HARDWARE,   // 使用硬件图形驱动创建一个设备。
			nullptr,                          // 除非驱动为D3D_DRIVER_TYPE_SOFTWARE，否则该值为0。
			deviceFlags,                // 设置debug和Direct2D兼容性标志。
			levels,                     // 这个应用可以支持的功能级别列表。
			ARRAYSIZE(levels),          // 上面列表的大小
			D3D11_SDK_VERSION,          // 对于Windows Store应用程序，始终将其设置为D3D11_SDK_VERSION。
			&device,                    // 返回创建的Direct3D设备
			&featureLevel,            // 返回创建的设备的特性级别
			&context                    // 返回设备的即时环境
		);
		if (FAILED(hr)) return hr;
		
		// 存储指向Direct3D 11.1 API设备和即时上下文的指针。
		device.As(&this->ptr);
		context.As(&deviceContext);
		return hr;
	}
	
	HRESULT GDevice::CreateRenderTargetView(GRenderTargetView &renderTargetView, const GTexture2D &texture)
	{
		if (!this->ptr) throw ENullptrException(__FUNCSIG__ TEXT(":: null device"));
		if (!texture) throw ENullptrException(__FUNCSIG__ TEXT(":: null texture"));
		return this->ptr->CreateRenderTargetView(texture.Get(), nullptr, renderTargetView.ReleaseAndGetAddressOf());
	}
	
	HRESULT GDevice::CreateDepthStencilView(GDepthStencilView &depthStencilView, const GTexture2D &texture)
	{
		if (!this->ptr) throw ENullptrException(__FUNCSIG__ TEXT(":: null device"));
		if (!texture) throw ENullptrException(__FUNCSIG__ TEXT(":: null texture"));
		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		return this->ptr->CreateDepthStencilView(
			texture.Get(), &depthStencilViewDesc, depthStencilView.ReleaseAndGetAddressOf());
	}
	
	GDevice *GDevice::Clone() const noexcept
	{
		auto *pDevice = new GDevice();
		pDevice->ptr = this->ptr;
		pDevice->featureLevel = this->featureLevel;
		return pDevice;
	}
	
	HRESULT GDevice::CreateTexture1D(GTexture1D &texture, const GTexture1D::Desc &desc)
	{
		return this->ptr->CreateTexture1D(&desc, nullptr, texture.ReleaseAndGetAddressOf());
	}
	
	HRESULT GDevice::CreateTexture2D(GTexture2D &texture, const GTexture2D::Desc &desc)
	{
		return this->ptr->CreateTexture2D(&desc, nullptr, texture.ReleaseAndGetAddressOf());
	}
	
	HRESULT GDevice::CreateTexture3D(GTexture3D &texture, const GTexture3D::Desc &desc)
	{
		return this->ptr->CreateTexture3D(&desc, nullptr, texture.ReleaseAndGetAddressOf());
	}
	
	HRESULT GDevice::GetAdapter(GDXGIAdapter &adapter)
	{
		if (!this->ptr) throw ENullptrException(__FUNCSIG__ TEXT(":: null device"));
		Microsoft::WRL::ComPtr<IDXGIDevice3> dxgiDevice;
		this->ptr.As(&dxgiDevice);
		return dxgiDevice->GetAdapter(adapter.ReleaseAndGetAddressOf());
	}
	
} // GenesisCubeEngine