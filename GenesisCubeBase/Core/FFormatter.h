#pragma once

#include "Header.h"
#include "FCore.h"

#ifdef UNICODE
#define GText(str) (GenesisCube::FFormatter::StringToWString(str))
#define FromGText(str) (GenesisCube::FFormatter::WStringToString(str))
#else
#define GText(str) (str)
#define FromGText(str) (str)
#endif

namespace GenesisCube
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
			Char chars[4];
			WChar wchars[2];
			char32_t uchar;
		};
	
	public:
		
		FFormatter() = delete;
		
		~FFormatter() = delete;
	
	public:
		
		///
		/// \param src_str GBK
		/// \return UTF-8
		static String GbkToUtf8(const String &src_str);
		
		///
		/// \param src_str UTF-8
		/// \return GBK
		static String Utf8ToGbk(const String &src_str);
		
		///
		/// \param s String
		/// \param m_encode
		/// \return WString
		static WString StringToWString(const String &s, UINT m_encode = CP_ACP);
		
		///
		/// \param s WString
		/// \param m_encode
		/// \return String
		static String WStringToString(const WString &s, UINT m_encode = CP_ACP);
		
		///
		/// 将特殊字符加上转义符号，例如'\\n'
		/// \param str
		/// \return
		static TString ToShowString(const TString &str);
		
		///
		/// 将转义符号转义，例如'\\n'
		/// \param str
		/// \return
		static TString FromShowString(const TString &str);
		
		///
		/// 格式化Windows错误
		///
		/// \param dwMessageId 消息ID
		/// \param dwLanguageId 语言ID
		/// \param dwBufferSize 缓冲区大小，包括'\0'字符，以TChar为单位
		/// \return 字符串
		static TString FormatMessageT
			(
				DWORD dwMessageId,
				DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				DWORD dwBufferSize = 256
			);
		
		/// 获取类型名
		template<class T>
		inline static TString GetTypeName()
		{
			return GText(typeid(T).name());
		}
		
		/// 获取类型名
		template<class Ptr>
		inline static TString GetTypeName(const Ptr &ptr)
		{
			return GText(typeid(*ptr).name());
		}
		
		
	};
	
}