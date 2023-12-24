//
// Created by admin on 2023/12/25.
//

#pragma once

#include "TUnknown.h"

namespace GenesisCubeEngine
{
	///
	/// 材质
	///
	class GTexture1D : public TUnknown<ID3D11Texture1D>
	{
	public:
		
		typedef D3D11_TEXTURE1D_DESC Desc;
	
	public:
		
		///
		/// \return
		[[nodiscard]]
		Desc GetDesc() const;
		
	};
	
	///
	/// 材质
	///
	class GTexture2D : public TUnknown<ID3D11Texture2D>
	{
	public:
		
		typedef D3D11_TEXTURE2D_DESC Desc;
	
	public:
		
		///
		/// 深度缓冲材质模板
		/// \param width 宽度
		/// \param height 高度
		/// \return
		static Desc DepthStencilDesc(uint32_t width, uint32_t height);
		
		///
		/// \return
		[[nodiscard]]
		Desc GetDesc() const;
		
	};
	
	///
	/// 材质
	///
	class GTexture3D : public TUnknown<ID3D11Texture3D>
	{
	public:
		
		typedef D3D11_TEXTURE3D_DESC Desc;
	
	public:
		
		///
		/// \return
		[[nodiscard]]
		Desc GetDesc() const;
		
	};
	
} // GenesisCubeEngine
