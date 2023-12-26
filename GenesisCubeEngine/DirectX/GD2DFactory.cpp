//
// Created by admin on 2023/12/27.
//

#include "GD2DFactory.h"

namespace GenesisCubeEngine
{
	HRESULT GD2DFactory::Create()
	{
		
		D2D1_FACTORY_OPTIONS options
			{
				.debugLevel = D2D1_DEBUG_LEVEL_ERROR
			};
		
		return D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(ID2D1Factory1),
			&options,
			&this->ptr
		);
	}
} // GenesisCubeEngine