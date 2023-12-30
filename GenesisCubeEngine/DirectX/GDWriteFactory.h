//
// Created by admin on 2023/12/27.
//

#pragma once

#include "TUnknown.h"
#include "GDWriteTextFormat.h"

namespace GenesisCube
{
	///
	/// DWrite工厂
	///
	class GDWriteFactory : public TUnknown<IDWriteFactory>
	{
	public:
		
		///
		/// 创建
		/// \return HRESULT
		[[nodiscard]]
		static FResult Create(IDWriteFactory **pFactory);
		
		///
		/// 创建
		/// \param textFormat 目标
		/// \param fontFamilyName 字体家族名称
		/// \param localeName 字体名字
		/// \param fontSize 字体大小
		/// \param fontWeight 字体宽度
		/// \param fontStyle 字体样式
		/// \param fontStretch 字体Stretch
		/// \return HRESULT
		[[nodiscard]]
		FResult CreateTextFormat(
			GDWriteTextFormat &textFormat, const TString &fontFamilyName, const TString &localeName, float fontSize,
			DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL
		);
		
	};
	
} // GenesisCube
