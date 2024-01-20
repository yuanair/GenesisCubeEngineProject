//
// Created by admin on 2024/1/19.
//

#include "FDWriteHelpers.h"

namespace GenesisCube
{
	HRESULT FDWriteHelpers::CreateFactory(TComPtr <IDWriteFactory> &factory)
	{
		return ::DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown **>(factory.ReleaseAndGetAddressOf()));
	}
} // GenesisCube