#include <sstream>
#include <iostream>
#include "Lexer.h"
#include "../Token/Tokens.h"
#include "../Token/ComparisonOperators.h"
#include "../Token/Brackets.h"
#include "../Token/ShiftOperators.h"
#include "../Token/AssignOperators.h"
#include "../Token/ShiftOperators.h"

using namespace GenesisCube::Token;

namespace GenesisCube::Lexer
{
	
	Lexer::Lexer()
		: ch(TEXT('\0')), pos(0LL), nextPos(0LL), tokenPos()
	{
	
	}
	
	Lexer::Lexer(const TString &file)
		: ch(TEXT('\0')), pos(0LL), nextPos(0LL), tokenPos(0LL, 1LL)
	{
		
		TIFStream ifs(file);
		if (!ifs.good()) throw ENotFindException(std::format(__FUNCSIG__ TEXT(":: file not found: \"{}\""), file));
		
		TOStringStream oss;
		oss << ifs.rdbuf();
		
		input = oss.str();
	}
	
	void Lexer::NextToken(TSharedPtr<Token::Token> &token)
	{
		ReadChar();
		SkipWhiteSpace();
		switch (ch)
		{
			case TEXT(':'):
			{
				if (PeekChar() == TEXT(':'))
				{
					token = NewToken<ScopeToken>();
					ReadChar();
					return;
				}
				else
				{
					NewError(Error::Error_Illegal, std::format(TEXT("invalid character '{}'"), ch));
					TString buffer;
					buffer.push_back(ch);
					token = NewToken<IllegalToken>(buffer);
				}
			}
			case TEXT(','):
			{
				token = NewToken<CommaToken>();
				return;
			}
			case TEXT('.'):
			{
				token = NewToken<PointToken>();
				return;
			}
			case TEXT('!'):
			{
				if (PeekChar() == TEXT('='))
				{
					token = NewToken<UnequalToken>();
					ReadChar();
					return;
				}
				else
				{
					token = NewToken<IllegalToken>(TEXT("!"));
					return;
				}
			}
			case TEXT('='):
			{
				if (PeekChar() == TEXT('='))
				{
					token = NewToken<EqualToken>();
					ReadChar();
					return;
				}
				else
				{
					
					token = NewToken<AssignmentToken>();
					return;
				}
			}
			case TEXT('<'):
			{
				TChar peekChar = PeekChar();
				if (peekChar == TEXT('='))
				{
					token = NewToken<LessThanEqualToken>();
					ReadChar();
					return;
				}
				else if (peekChar == TEXT('<'))
				{
					token = NewToken<LeftShiftToken>();
					ReadChar();
					return;
				}
				else
				{
					token = NewToken<LessThanToken>();
					return;
				}
			}
			case TEXT('>'):
			{
				TChar peekChar = PeekChar();
				if (peekChar == TEXT('='))
				{
					token = NewToken<GreaterThanEqualToken>();
					ReadChar();
					return;
				}
				else if (peekChar == TEXT('>'))
				{
					token = NewToken<RightShiftToken>();
					ReadChar();
					return;
				}
				else
				{
					token = NewToken<GreaterThanToken>();
					return;
				}
			}
			case TEXT('+'):
			{
				token = NewToken<PlusToken>();
				return;
			}
			case TEXT('-'):
			{
				token = NewToken<MinusToken>();
				return;
			}
			case TEXT('*'):
			{
				token = NewToken<MultiplyToken>();
				return;
			}
			case TEXT('%'):
			{
				token = NewToken<ModToken>();
				return;
			}
			case TEXT('/'):
			{
				TChar peekChar = PeekChar();
				if (peekChar == TEXT('/'))
				{
					do ReadChar();
					while (ch != TEXT('\n') && ch != TEXT('\0'));
					NextToken(token);
					return;
				}
				else if (peekChar == TEXT('*'))
				{
					do
					{
						ReadChar();
						if (ch == TEXT('*'))
						{
							if (PeekChar() == TEXT('/'))
							{
								break;
							}
						}
					}
					while (ch != TEXT('\0'));
					NextToken(token);
					return;
				}
				else
				{
					token = NewToken<DivideToken>();
					return;
				}
			}
			case TEXT('('):
			{
				token = NewToken<LeftParenToken>();
				return;
			}
			case TEXT(')'):
			{
				token = NewToken<RightParenToken>();
				return;
			}
			case TEXT('['):
			{
				token = NewToken<LeftBracketToken>();
				return;
			}
			case TEXT(']'):
			{
				token = NewToken<RightBracketToken>();
				return;
			}
			case TEXT('{'):
			{
				token = NewToken<LeftBraceToken>();
				return;
			}
			case TEXT('}'):
			{
				token = NewToken<RightBraceToken>();
				return;
			}
			case TEXT(';'):
			{
				token = NewToken<SemicolonToken>();
				return;
			}
			case TEXT('\0'):
			{
				token = NewToken<EOFToken>();
				return;
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
			{
				ReadNumber(token);
				UnreadChar();
				return;
			}
			case TEXT('"'):
			{
				TString buffer;
				ReadChar();
				ReadString(buffer, '"');
				token = NewToken<StringToken>(buffer);
				return;
			}
			case TEXT('\''):
			{
				TString buffer;
				ReadChar();
				ReadString(buffer, '\'');
				if (buffer.empty())
				{
					NewError(Error::Error_ErrorChar, TEXT("empty character"));
					token = NewToken<IllegalToken>(buffer);
				}
				else if (buffer.size() == 1)
				{
					token = NewToken<CharToken>(buffer[0]);
				}
				else
				{
					NewError(Error::Error_ErrorChar, TEXT("redundant character"));
					token = NewToken<IllegalToken>(buffer);
				}
				return;
			}
			case TEXT('_'):
			case TEXT('@'):
			{
				ReadIdentifier(token);
				UnreadChar();
				return;
			}
			default:
			{
				if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
				{
					ReadIdentifier(token);
					UnreadChar();
					return;
				}
				else
				{
					NewError(Error::Error_Illegal, std::format(TEXT("invalid character '{}'"), ch));
					TString buffer;
					buffer.push_back(ch);
					token = NewToken<IllegalToken>(buffer);
					return;
				}
			}
		}
	}
	
	Token::TokenPos GenesisCube::Lexer::Lexer::GetTokenPos() const
	{
		return this->tokenPos;
	}
	
	void Lexer::SkipWhiteSpace()
	{
		while (isspace(ch))
		{
			ReadChar();
		}
	}
	
	void Lexer::ReadChar()
	{
		if (nextPos >= input.length())
		{
			ch = 0;
		}
		else
		{
			ch = input[nextPos];
			if (ch == TEXT('\n'))
			{
				tokenPos.line++;
				tokenPos.ch = 0LL;
			}
			else
			{
				tokenPos.ch++;
			}
		}
		pos = nextPos;
		nextPos++;
	}
	
	void Lexer::UnreadChar()
	{
		nextPos = pos;
		pos--;
	}
	
	void Lexer::ReadNumber(TSharedPtr<Token::Token> &token)
	{
		TString buffer;
		bool bIsFloat = false;
		while ((ch >= TEXT('0') && ch <= TEXT('9')) || ch == TEXT('.'))
		{
			buffer.push_back(ch);
			ReadChar();
			if (ch == TEXT('.'))
			{
				if (bIsFloat)
				{
					NewError(Error::Error_ErrorNumber, TEXT("Multiple decimal points"));
					while ((ch >= TEXT('0') && ch <= TEXT('9')) || ch == TEXT('.'))
						ReadChar();
					token = NewToken<IllegalToken>(buffer);
					return;
				}
				bIsFloat = true;
			}
		}
		if (bIsFloat)
		{
#ifdef UNICODE
			token = NewToken<FloatToken>(_wtof(buffer.c_str()));
#else
			token = NewToken<FloatToken>(std::atof(buffer.c_str()));
#endif
			return;
		}
#ifdef UNICODE
		token = NewToken<IntegerToken>(_wtoi(buffer.c_str()));
#else
		token = NewToken<IntegerToken>(std::atoi(buffer.c_str()));
#endif
	}
	
	void Lexer::ReadString(TString &buffer, TChar stopChar)
	{
		for (; ch != stopChar; ReadChar())
		{
			if (ch != TEXT('\\'))
			{
				buffer.push_back(ch);
				continue;
			}
			if (ch == TEXT('\0'))
			{
				NewError(Error::Error_ErrorChar, TEXT("error char: '\\0'"));
				return;
			}
			ReadChar();
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
				case TEXT('0'):
				case TEXT('1'):
				case TEXT('2'):
				case TEXT('3'):
				case TEXT('4'):
				case TEXT('5'):
				case TEXT('6'):
				case TEXT('7'):
				{
					//
					//buffer.push_back(TEXT('\x'));
					break;
				}
				case TEXT('u'):
				case TEXT('x'):
				{
					ReadChar();
					NumberToChars number{};
					ReadHex(number, 8);
					UnreadChar();
					if (number.wStr[1] == 0)
					{
						buffer.push_back(number.str[0]);
						buffer.push_back(number.str[1]);
						break;
					}
					buffer.append(number.tStr, sizeof(number.tStr) / sizeof(number.tStr[0]));
					break;
				}
				case TEXT('"'):
				case TEXT('\''):
				case TEXT('\\'):
				case TEXT('\?'):
					buffer.push_back(ch);
					break;
				case TEXT('\0'):
					NewError(Error::Error_ErrorChar, TEXT("error char: '\\0'"));
					break;
				default:
					buffer.push_back(ch);
					NewError(Error::Warning_ErrorChar, std::format(TEXT("unknown escape sequence: '\\{}'"), ch));
					break;
			}
		}
	}
	
	
	void Lexer::ReadIdentifier(TSharedPtr<Token::Token> &token)
	{
		TString buffer;
		while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || ch == '@')
		{
			buffer.push_back(ch);
			ReadChar();
		}
		token = NewToken<IdentifierToken>(buffer);
	}
	
	TChar Lexer::PeekChar()
	{
		return input[nextPos];
	}
	
	void Lexer::NewError(Lexer::Error::Type type, const TString &message)
	{
		errors.emplace_back(type, message, tokenPos);
	}
	
	Lexer *Lexer::Clone() const noexcept
	{
		auto lexer = new Lexer;
		lexer->input = input;
		return lexer;
	}
	
	void Lexer::ReadHex(NumberToChars &number, int32_t count)
	{
		std::vector<uint8_t> buffer;
		for (; count > 0; count--, ReadChar())
		{
			if (ch >= TEXT('0') && ch <= TEXT('9'))
				buffer.push_back(ch - TEXT('0'));
			else if (ch >= TEXT('a') && ch <= TEXT('f'))
				buffer.push_back(ch - TEXT('a'));
			else if (ch >= TEXT('A') && ch <= TEXT('F'))
				buffer.push_back(ch - TEXT('A'));
			else break;
		}
		number.number = 0;
		if (buffer.empty()) return;
		int32_t hex = 1;
		for (size_t index = buffer.size() - 1; index < buffer.size(); index--)
		{
			number.number += buffer[index] * hex;
			hex <<= 4;
		}
	}
	
	
}