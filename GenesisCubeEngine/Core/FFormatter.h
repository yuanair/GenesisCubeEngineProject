#pragma once

#include "Header.h"
#include "../Exception/Exception.h"

namespace GenesisCubeEngine
{
	
	/// <summary>
	/// 格式化类
	/// </summary>
	class FFormatter
	{
	public:
		
		union NumberToChars
		{
			int32_t number;
			char chars[4];
			wchar_t wchars[2];
			char32_t uchar;
		};
	
	public:
		
		FFormatter() = delete;
		
		~FFormatter() = delete;
	
	public:
		
		static String GbkToUtf8(const String &src_str);
		
		static String Utf8ToGbk(const String &src_str);
		
		static WString StringToWString(const String &s, UINT m_encode = CP_ACP);
		
		static String WStringToString(const WString &s, UINT m_encode = CP_ACP);
		
		static TString ToShowString(const TString &str);
		
		static TString FromShowString(const TString &str);
		
		
	};
	
}