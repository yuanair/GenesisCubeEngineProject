//
// Created by admin on 2023/12/27.
//

#include "GDWriteFactory.h"

namespace GenesisCubeEngine
{
	HRESULT GDWriteFactory::Create()
	{
		DWRITE_FACTORY_TYPE type = DWRITE_FACTORY_TYPE_SHARED;
		return DWriteCreateFactory(
			type, __uuidof(this->ptr), reinterpret_cast<IUnknown **>(this->ptr.ReleaseAndGetAddressOf()));
	}
	
	HRESULT GDWriteFactory::CreateTextFormat(GDWriteTextFormat &textFormat, const TString &fontFamilyName,
											 DWRITE_FONT_WEIGHT fontWeight,
											 DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch,
											 float fontSize, const TString &localeName)
	{
		return this->ptr->CreateTextFormat(
			fontFamilyName.c_str(), nullptr, fontWeight, fontStyle, fontStretch, fontSize, localeName.c_str(),
			textFormat.ReleaseAndGetAddressOf());
	}
} // GenesisCubeEngine