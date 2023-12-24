//
// Created by admin on 2023/12/24.
//

#pragma once

#include "TUnknown.h"
#include "GDeviceContext.h"
#include "GRenderTargetView.h"
#include "GDepthStencilView.h"
#include "GDXGIFactory.h"
#include "Texture.h"
#include "GDXGIAdapter.h"

namespace GenesisCubeEngine
{
	///
	/// D3D设备
	///
	class GDevice : public TUnknown<ID3D11Device>
	{
	public:
		
		GDevice() noexcept = default;
		
		~GDevice() noexcept override = default;
	
	public:
		
		///
		/// 自动创建
		///
		/// \param deviceContext 用于存储设备环境
		/// \param adapter 用于存储适配器
		/// \param factory 用于存储工厂
		/// \return
		HRESULT AutoCreate(GDeviceContext &deviceContext, GDXGIAdapter &adapter, GDXGIFactory &factory);
		
		///
		/// 创建
		///
		/// \param deviceContext 用于存储设备环境
		/// \return
		HRESULT Create(GDeviceContext &deviceContext);
		
		///
		/// 创建渲染目标视图
		///
		/// \param renderTargetView 用于存储渲染目标视图
		/// \param texture 材质
		/// \return
		HRESULT CreateRenderTargetView(GRenderTargetView &renderTargetView, const GTexture2D &texture);
		
		///
		/// 创建深度缓冲区视图
		/// \param depthStencilView 用于存储深度视图
		/// \param texture 材质
		/// \return
		HRESULT CreateDepthStencilView(GDepthStencilView &depthStencilView, const GTexture2D &texture);
		
		///
		/// 创建材质
		/// \param texture 材质
		/// \param desc
		/// \return
		HRESULT CreateTexture1D(GTexture1D &texture, const GTexture1D::Desc &desc);
		
		///
		/// 创建材质
		/// \param texture 材质
		/// \param desc
		/// \return
		HRESULT CreateTexture2D(GTexture2D &texture, const GTexture2D::Desc &desc);
		
		///
		/// 创建材质
		/// \param texture 材质
		/// \param desc
		/// \return
		HRESULT CreateTexture3D(GTexture3D &texture, const GTexture3D::Desc &desc);
		
		///
		/// 获取适配器
		/// \param adapter 适配器
		/// \return
		HRESULT GetAdapter(GDXGIAdapter &adapter);
	
	public:
		
		///
		/// \return 功能等级
		[[nodiscard]]
		inline D3D_FEATURE_LEVEL GetFeatureLevel() const noexcept { return this->featureLevel; }
		
		[[nodiscard]]
		GDevice *Clone() const noexcept override;
	
	private:
		
		D3D_FEATURE_LEVEL featureLevel = {};
		
	};
	
} // GenesisCubeEngine
