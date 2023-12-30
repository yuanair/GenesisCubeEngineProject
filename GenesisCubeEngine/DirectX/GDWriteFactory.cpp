//
// Created by admin on 2023/12/27.
//

#include "GDWriteFactory.h"

namespace GenesisCube
{
	FResult GDWriteFactory::Create(IDWriteFactory **pFactory)
	{
		DWRITE_FACTORY_TYPE type = DWRITE_FACTORY_TYPE_SHARED;
		return DWriteCreateFactory(
			type, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown **>(pFactory));
	}
	
	FResult GDWriteFactory::CreateTextFormat(GDWriteTextFormat &textFormat, const TString &fontFamilyName,
											 const TString &localeName, float fontSize, DWRITE_FONT_WEIGHT fontWeight,
											 DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch)
	{
		ThrowIfNull();
		return GetComPtr()->CreateTextFormat(
			fontFamilyName.c_str(), nullptr, fontWeight, fontStyle, fontStretch, fontSize, localeName.c_str(),
			textFormat.ReleaseAndGetAddressOf());
	}
} // GenesisCube