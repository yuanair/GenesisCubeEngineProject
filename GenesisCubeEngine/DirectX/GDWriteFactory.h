//
// Created by admin on 2023/12/27.
//

#pragma once

#include "TUnknown.h"
#include "GDWriteTextFormat.h"

namespace GenesisCubeEngine
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
		HRESULT Create();
		
		///
		/// 创建
		/// \param textFormat 目标
		/// \param fontFamilyName 字体家族名称
		/// \param fontWeight 字体宽度
		/// \param fontStyle 字体样式
		/// \param fontStretch 字体Stretch
		/// \param fontSize 字体大小
		/// \param localeName 字体名字
		/// \return HRESULT
		[[nodiscard]]
		HRESULT CreateTextFormat(
			GDWriteTextFormat &textFormat, const TString &fontFamilyName, DWRITE_FONT_WEIGHT fontWeight,
			DWRITE_FONT_STYLE fontStyle,
			DWRITE_FONT_STRETCH fontStretch, float fontSize, const TString &localeName
		);
		
	};
	
} // GenesisCubeEngine
