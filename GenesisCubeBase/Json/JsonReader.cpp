#include "JsonReader.h"

namespace GenesisCube
{
	
	JSON::JsonReader::JsonReader(TIStream &source)
		: source(source)
	{
		if (source.bad())
		{
			this->ch = TEXT('\0');
		}
		else
		{
			this->ch = source.get();
		}
	}
	
	JSON::JsonReader::~JsonReader()
	= default;
	
	bool JSON::JsonReader::Eof() const
	{
		return this->source.eof();
	}
	
	TString JSON::JsonReader::ReadString(TCHAR stopChar)
	{
		TString buffer;
		do
		{
			if (ch == stopChar)
			{
				NextChar();
				break;
			}
			else if (ch == TEXT('\\'))
			{
				TCHAR cbuffer[5] = {};
				union NumberToChars
				{
					int number;
					char chars[4];
					wchar_t wchars[2];
				} num = {};
				if (!NextChar()) return buffer;
				switch (ch)
				{
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
					case TEXT('u'):
						
						for (int j = 0; j < 4; j++)
						{
							if (!NextChar()) return buffer;
							cbuffer[j] = ch;
						}
#ifdef UNICODE
						swscanf_s(cbuffer, L"%x", &num.number);
						wcsncpy_s(cbuffer, num.wchars, 2);
#else
						sscanf(cbuffer, "%x", &num.number);
						strncpy_s(cbuffer, num.chars, 4);
#endif
						buffer.append(cbuffer);
						break;
						// case TEXT('\\'):case TEXT('\"'):case TEXT('\''):
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
		while (NextChar());
		return buffer;
	}
	
	bool JSON::JsonReader::NextChar()
	{
		if (Eof())
		{
			this->ch = TEXT('\0');
			return false;
		}
		this->ch = this->source.get();
		return true;
	}
	
	bool JSON::JsonReader::UnnextChar()
	{
		this->source.unget();
		return true;
	}
	
	bool JSON::JsonReader::Good() const
	{
		return Eof();
	}
	
	TPtr<JSON::Json> JSON::JsonReader::Next()
	{
		do
		{
			switch (this->ch)
			{
				case TEXT('\"'):
				{
					if (!NextChar()) return MakePtr<Json>(TEXT("<error string>"));
					return MakePtr<Json>(ReadString(TEXT('\"')));
				}
				case TEXT('\''):
				{
					if (!NextChar()) return MakePtr<Json>(TEXT("<error string>"));
					return MakePtr<Json>(ReadString(TEXT('\'')));
				}
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
				case TEXT('-'):
				case TEXT('+'):
				{
					TString buffer;
					bool bIsFloat = false;
					bool bError = false;
					buffer.push_back(ch);
					NextChar();
					do
					{
						buffer.push_back(ch);
						if (ch == TEXT('.'))
						{
							if (bIsFloat) bError = true;
							else bIsFloat = true;
							if (!NextChar())
							{
								bError = true;
								break;
							}
						}
						else if (ch == TEXT('e'))
						{
							if (bIsFloat) bError = true;
							else bIsFloat = true;
							if (!NextChar())
							{
								bError = true;
								break;
							}
							if ((ch < TEXT('0') || ch > TEXT('9')) && ch != TEXT('+') && ch != TEXT('-'))
							{
								UnnextChar();
								bError = true;
								break;
							}
							buffer.push_back(ch);
							if (!NextChar())
							{
								bError = true;
								break;
							}
						}
						else if (ch < TEXT('0') || ch > TEXT('9'))
						{
							UnnextChar();
							break;
						}
						else
						{
							if (!NextChar()) break;
						}
					}
					while (true);
					
					if (bError) return MakePtr<Json>(TEXT("<error number>"));
					
					if (bIsFloat)
					{
						return MakePtr<Json>(std::stof(buffer));
					}
					else
					{
						return MakePtr<Json>(std::stoll(buffer));
					}
				}
				case TEXT('f'):
				{
					bool bError = false;
					if (!NextChar() || ch != TEXT('a')) bError = true;
					if (!NextChar() || ch != TEXT('l')) bError = true;
					if (!NextChar() || ch != TEXT('s')) bError = true;
					if (!NextChar() || ch != TEXT('e')) bError = true;
					if (bError) return MakePtr<Json>(TEXT("<error>"));
					return MakePtr<Json>(false);
				}
				case TEXT('t'):
				{
					bool bError = false;
					if (!NextChar() || ch != TEXT('r')) bError = true;
					if (!NextChar() || ch != TEXT('u')) bError = true;
					if (!NextChar() || ch != TEXT('e')) bError = true;
					if (bError) return MakePtr<Json>(TEXT("<error>"));
					return MakePtr<Json>(true);
				}
				case TEXT('{'):
				{
					if (!NextChar()) return MakePtr<Json>(TEXT("<error object>"));
					return ReadObject();
				}
				case TEXT('['):
				{
					if (!NextChar()) return MakePtr<Json>(TEXT("<error array>"));
					return ReadArray();
				}
				case TEXT('n'):
				{
					bool bError = false;
					if (!NextChar() || ch != TEXT('u')) bError = true;
					if (!NextChar() || ch != TEXT('l')) bError = true;
					if (!NextChar() || ch != TEXT('l')) bError = true;
					if (bError) return MakePtr<Json>(TEXT("<error>"));
					return MakePtr<Json>(nullptr);
				}
				case TEXT(' '):
				case TEXT('\f'):
				case TEXT('\n'):
				case TEXT('\r'):
				case TEXT('\t'):
				case TEXT('\v'):
				{
					// space char
				}
					break;
				case TEXT('/'):
				{
					if (!NextChar()) return MakePtr<Json>(TEXT("<error>"));
					if (ch == TEXT('/'))
					{
						while (NextChar())
						{
							if (ch == TEXT('\n')) break;
						}
					}
					else if (ch == TEXT('*'))
					{
						while (NextChar())
						{
							if (ch == TEXT('*'))
							{
								if (!NextChar()) return MakePtr<Json>(TEXT("<error>"));
								if (ch == TEXT('/')) break;
							}
						}
					}
					else
					{
						return MakePtr<Json>(TEXT("<error>"));
					}
				}
					break;
				default:
				{
					//return MakePtr< Json(TEXT("<error>"));
				}
					break;
			}
		}
		while (NextChar());
		return MakePtr<Json>(nullptr);
	}
	
	TPtr<JSON::Json> JSON::JsonReader::ReadArray()
	{
		auto json = MakePtr<Json>();
		do
		{
			if (ch == TEXT(']')) break;
			if ((ch >= TEXT('\t') && ch <= TEXT('\r')) || ch == TEXT(' ') || ch == TEXT(','))
			{
			
			}
			else
			{
				auto ptr = Next();
				json->Push(*ptr);
			}
		}
		while (NextChar());
		return json;
	}
	
	TPtr<JSON::Json> JSON::JsonReader::ReadObject()
	{
		auto json = MakePtr<Json>();
		do
		{
			if (ch == TEXT('}')) break;
			if ((ch >= TEXT('\t') && ch <= TEXT('\r')) || ch == TEXT(' ') || ch == TEXT(','))
			{
			
			}
			else
			{
				auto key = Next();
				do
				{
					if (ch == TEXT(':')) break;
				}
				while (NextChar());
				if (key->Is<GString>())
				{
					TString buffer = key->operator TString();
					auto ptr = Next();
					json->operator[](buffer) = *ptr;
				}
			}
		}
		while (NextChar());
		return json;
	}
	
	GObject *JSON::JsonReader::Clone() const noexcept
	{
		return new JsonReader(this->source);
	}
	
}
