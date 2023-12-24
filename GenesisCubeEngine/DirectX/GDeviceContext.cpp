//
// Created by admin on 2023/12/24.
//

#include "GDeviceContext.h"

namespace GenesisCubeEngine
{
	
	void GDeviceContext::RSSetViewports(std::vector<D3D11_VIEWPORT> viewports)
	{
		this->ptr->RSSetViewports(viewports.size(), viewports.data());
	}
	
	void GDeviceContext::ClearRenderTargetView(const GRenderTargetView &renderTargetView, DirectX::XMFLOAT4 color)
	{
		this->ptr->ClearRenderTargetView(renderTargetView.Get(), (float *) &color);
	}
	
	void GDeviceContext::ClearDepthStencilView(const GDepthStencilView &depthStencilView, float depth, uint8_t stencil)
	{
		this->ptr->ClearDepthStencilView(
			depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil
		);
	}
	
	void GDeviceContext::OMSetRenderTargets(std::vector<GRenderTargetView::TUnknown::Type *> &renderTargetView,
											const GDepthStencilView &depthStencilView)
	{
		if (renderTargetView.empty()) return this->ptr->OMSetRenderTargets(0, nullptr, depthStencilView.Get());
		auto buffer = renderTargetView.data();
		this->ptr->OMSetRenderTargets(
			renderTargetView.size(), buffer,
			depthStencilView.Get());
	}
} // GenesisCubeEngine