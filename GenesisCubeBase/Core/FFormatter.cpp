#include "FFormatter.h"

namespace GenesisCube
{
	
	String FFormatter::GbkToUtf8(const String &src_str)
	{
		int32_t len = MultiByteToWideChar(CP_ACP, 0, src_str.c_str(), -1, nullptr, 0);
		auto *wStr = new WChar[len + 1];
		memset(wStr, 0, len + 1LL);
		MultiByteToWideChar(CP_ACP, 0, src_str.c_str(), -1, wStr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wStr, -1, nullptr, 0, nullptr, nullptr);
		auto *str = new Char[len + 1];
		memset(str, 0, len + 1LL);
		WideCharToMultiByte(CP_UTF8, 0, wStr, -1, str, len, nullptr, nullptr);
		String strTemp = str;
		delete[] wStr;
		delete[] str;
		return strTemp;
	}
	
	String FFormatter::Utf8ToGbk(const String &src_str)
	{
		int32_t len = MultiByteToWideChar(CP_UTF8, 0, src_str.c_str(), -1, nullptr, 0);
		auto *wszGBK = new WChar[len + 1];
		memset(wszGBK, 0, len * 2LL + 2LL);
		MultiByteToWideChar(CP_UTF8, 0, src_str.c_str(), -1, wszGBK, len);
		len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, nullptr, 0, nullptr, nullptr);
		auto *szGBK = new Char[len + 1];
		memset(szGBK, 0, len + 1LL);
		WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, nullptr, nullptr);
		String strTemp(szGBK);
		delete[] wszGBK;
		delete[] szGBK;
		return strTemp;
	}
	
	
	WString FFormatter::StringToWString(const String &s, UINT m_encode)
	{
		WString str;
		int32_t len = MultiByteToWideChar(m_encode, 0, s.c_str(), (int32_t) s.size(), nullptr, 0);
		auto *m_wchar = new WChar[len + 1];
		MultiByteToWideChar(m_encode, 0, s.c_str(), (int32_t) s.size(), m_wchar, len);
		m_wchar[len] = L'\0';
		str = m_wchar;
		delete[] m_wchar;
		return str;
	}
	
	String FFormatter::WStringToString(const WString &s, UINT m_encode)
	{
		String str;
		int32_t len = WideCharToMultiByte(m_encode, 0, s.c_str(), (int32_t) s.size(), nullptr, 0, nullptr, nullptr);
		Char *m_char = new Char[len + 1];
		WideCharToMultiByte(m_encode, 0, s.c_str(), (int32_t) s.size(), m_char, len, nullptr, nullptr);
		m_char[len] = '\0';
		str = m_char;
		delete[] m_char;
		return str;
	}
	
	TString FFormatter::ToShowString(const TString &str)
	{
		TString buffer;
		
		for (wchar_t ch: str)
		{
			switch (ch)
			{
				case TEXT('\a'):
					buffer.push_back(TEXT('\\'));
					buffer.push_back(TEXT('a'));
					break;
				case TEXT('\b'):
					buffer.push_back(TEXT('\\'));
					buffer.push_back(TEXT('b'));
					break;
				case TEXT('\f'):
					buffer.push_back(TEXT('\\'));
					buffer.push_back(TEXT('f'));
					break;
				case TEXT('\n'):
					buffer.push_back(TEXT('\\'));
					buffer.push_back(TEXT('n'));
					break;
				case TEXT('\r'):
					buffer.push_back(TEXT('\\'));
					buffer.push_back(TEXT('r'));
					break;
				case TEXT('\t'):
					buffer.push_back(TEXT('\\'));
					buffer.push_back(TEXT('t'));
					break;
				case TEXT('\v'):
					buffer.push_back(TEXT('\\'));
					buffer.push_back(TEXT('v'));
					break;
				case TEXT('\0'):
					buffer.push_back(TEXT('\\'));
					buffer.push_back(TEXT('0'));
					break;
				case TEXT('\\'):
				case TEXT('\"'):
				case TEXT('\''):
					buffer.push_back(TEXT('\\'));
					buffer.push_back(ch);
					break;
				default:
					buffer.push_back(ch);
					break;
			}
		}
		
		return buffer;
	}
	
	TString FFormatter::FromShowString(const TString &str)
	{
		TString buffer;
		
		for (size_t i = 0; i < str.size(); i++)
		{
			TCHAR ch = str[i];
			if (ch == TEXT('\\'))
			{
				if (i == str.size() - 1)
				{
					buffer.push_back(TEXT('\\'));
					break;
				}
				TCHAR cBuffer[9] = {};
				NumberToChars num = {};
				ch = str[++i];
				switch (ch)
				{
					case TEXT('a'):
						buffer.push_back(TEXT('\a'));
						break;
					case TEXT('b'):
						buffer.push_back(TEXT('\b'));
						break;
					case TEXT('f'):
						buffer.push_back(TEXT('\f'));
						break;
					case TEXT('n'):
						buffer.push_back(TEXT('\n'));
						break;
					case TEXT('r'):
						buffer.push_back(TEXT('\r'));
						break;
					case TEXT('t'):
						buffer.push_back(TEXT('\t'));
						break;
					case TEXT('v'):
						buffer.push_back(TEXT('\v'));
						break;
					case TEXT('u'):
						i++;
						for (int j = 0; i < str.size() && j < 4; i++, j++)
						{
							cBuffer[j] = str[i];
						}
						i--;
#ifdef UNICODE
						swscanf_s(cBuffer, L"%x", &num.number);
						wcsncpy_s(cBuffer, num.wchars, 2);
#else
						sscanf(cBuffer, "%x", &num.number);
						strncpy_s(cBuffer, num.chars, 4);
#endif
						buffer.append(cBuffer);
						break;
					case TEXT('x'):
						i++;
						for (int j = 0; i < str.size() && j < 2; i++, j++)
						{
							cBuffer[j] = str[i];
						}
						i--;
#ifdef UNICODE
						swscanf_s(cBuffer, L"%x", &num.number);
						wcsncpy_s(cBuffer, num.wchars, 2);
#else
						sscanf(cBuffer, "%x", &num.number);
						strncpy_s(cBuffer, num.chars, 4);
#endif
						buffer.append(cBuffer);
						break;
					case TEXT('U'):
						i++;
						for (int j = 0; i < str.size() && j < 8; i++, j++)
						{
							cBuffer[j] = str[i];
						}
						i--;
#ifdef UNICODE
						swscanf_s(cBuffer, L"%x", &num.number);
						wcsncpy_s(cBuffer, num.wchars, 2);
#else
						sscanf(cBuffer, "%x", &num.number);
						strncpy_s(cBuffer, num.chars, 4);
#endif
						buffer.append(cBuffer);
						break;
					case TEXT('0'):
					case TEXT('1'):
					case TEXT('2'):
					case TEXT('3'):
					case TEXT('4'):
					case TEXT('5'):
					case TEXT('6'):
					case TEXT('7'):
					case TEXT('8'):
					case TEXT('9'):
						for (int j = 0; i < str.size() && j < 3; i++, j++)
						{
							cBuffer[j] = str[i];
						}
						i--;
#ifdef UNICODE
						swscanf_s(cBuffer, L"%o", &num.number);
						wcsncpy_s(cBuffer, num.wchars, 2);
#else
						sscanf(cBuffer, "%o", &num.number);
						strncpy_s(cBuffer, num.chars, 4);
#endif
						buffer.append(cBuffer);
						break;
					case TEXT('\\'):
					case TEXT('\"'):
					case TEXT('\''):
					default:
						buffer.push_back(ch);
						break;
				}
			}
			else
			{
				buffer.push_back(ch);
			}
		}
		
		return buffer;
	}
	
	
	TString FFormatter::GFormatMessage(DWORD dwMessageId, DWORD dwLanguageId, DWORD dwBufferSize)
	{
		auto strBufferError = new TChar[dwBufferSize];
		FormatMessage
			(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr, dwMessageId, dwLanguageId,
				strBufferError, dwBufferSize, nullptr
			);
		TString buffer = strBufferError;
		delete[] strBufferError;
		return buffer;
	}
	
}