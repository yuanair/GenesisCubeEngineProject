//
// Created by admin on 2023/12/25.
//

#include "GDXGISwapChain.h"

namespace GenesisCubeEngine
{
	
	HRESULT GDXGISwapChain::GetBuffer(GTexture2D &texture, uint32_t buffer)
	{
		if (!this->ptr) throw ENullptrException(__FUNCSIG__ TEXT(":: null swapChain"));
		return this->ptr->GetBuffer
			(
				buffer,
				__uuidof(GTexture2D::TUnknown::Type),
				(void **) texture.ReleaseAndGetAddressOf()
			);
	}
	
	HRESULT GDXGISwapChain::Present()
	{
		return this->ptr->Present(0, 0);
	}
} // GenesisCubeEngine