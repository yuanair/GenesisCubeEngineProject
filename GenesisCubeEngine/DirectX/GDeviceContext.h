//
// Created by admin on 2023/12/24.
//

#pragma once

#include "TUnknown.h"
#include "GRenderTargetView.h"
#include "GDepthStencilView.h"

namespace GenesisCubeEngine
{
	///
	/// D3D设备环境
	///
	class GDeviceContext : public TUnknown<ID3D11DeviceContext>
	{
	public:
		
		GDeviceContext() = default;
		
		~GDeviceContext() override = default;
	
	public:
		
		///
		/// 设置视图
		/// \param viewports 视图
		void RSSetViewports(std::vector<D3D11_VIEWPORT> viewports);
		
		///
		/// 清空渲染目标视图
		/// \param renderTargetView 渲染目标视图
		/// \param color 颜色
		void ClearRenderTargetView(const GRenderTargetView &renderTargetView, DirectX::XMFLOAT4 color);
		
		///
		/// 清空深度视图
		/// \param depthStencilView 深度视图
		/// \param depth 深度
		/// \param stencil 模具
		void ClearDepthStencilView(const GDepthStencilView &depthStencilView, float depth = 1.0f, uint8_t stencil = 0);
		
		///
		/// 设置渲染目标
		/// \param renderTargetViews 渲染目标视图
		/// \param depthStencilView 深度视图
		void OMSetRenderTargets(std::vector<GRenderTargetView::TUnknown::Type *> &renderTargetViews,
								const GDepthStencilView &depthStencilView);
		
	};
	
} // GenesisCubeEngine
