//
// Created by admin on 2023/12/25.
//

#include "Texture.h"

namespace GenesisCubeEngine
{
	
	
	GTexture2D::Desc GTexture2D::DepthStencilDesc(uint32_t width, uint32_t height)
	{
		return
			{
				.Width = width,
				.Height = height,
				.MipLevels = 1,
				.ArraySize = 1,
				.Format = DXGI_FORMAT_D24_UNORM_S8_UINT,
				.SampleDesc =
					{
						.Count = 1,
						.Quality = 0
					},
				.Usage = D3D11_USAGE_DEFAULT,
				.BindFlags = D3D11_BIND_DEPTH_STENCIL,
				.CPUAccessFlags = 0,
				.MiscFlags = 0
			};
	}
	
	GTexture1D::Desc GTexture1D::GetDesc() const
	{
		Desc desc;
		this->ptr->GetDesc(&desc);
		return desc;
	}
	
	GTexture2D::Desc GTexture2D::GetDesc() const
	{
		Desc desc;
		this->ptr->GetDesc(&desc);
		return desc;
	}
	
	GTexture3D::Desc GTexture3D::GetDesc() const
	{
		Desc desc;
		this->ptr->GetDesc(&desc);
		return desc;
	}
	
} // GenesisCubeEngine