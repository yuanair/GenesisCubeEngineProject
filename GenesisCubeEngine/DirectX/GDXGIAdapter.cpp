//
// Created by admin on 2023/12/25.
//

#include "GDXGIAdapter.h"
#include "GDXGIFactory.h"

namespace GenesisCubeEngine
{
	
	HRESULT GDXGIAdapter::GetParent(GDXGIFactory &factory)
	{
		if (!this->ptr) throw ENullptrException(__FUNCSIG__ TEXT(":: null adapter"));
		return this->ptr->GetParent(IID_PPV_ARGS(factory.ReleaseAndGetAddressOf()));
	}
	
} // GenesisCubeEngine