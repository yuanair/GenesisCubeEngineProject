#include "Lexer.h"
#include "../Token/Tokens.h"

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
		if (!ifs.good())
		{
			std::wcerr << TEXT("file not found: \"") << file << TEXT("\"") << std::endl;
			return;
		}
		
		TOStringStream oss;
		oss << ifs.rdbuf();
		
		input = oss.str();
	}
	
	void Lexer::NextToken(TPtr<Token::Token> &token)
	{
		ReadChar();
		SkipWhiteSpace();
		switch (ch)
		{
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
				ReadChar();
				ReadString(token, '"');
				return;
			}
			case TEXT('\''):
			{
				ReadChar();
				ReadString(token, '\'');
				return;
			}
			default:
			{
				if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || ch == '@')
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
	
	void Lexer::ReadNumber(TPtr<Token::Token> &token)
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
				else
				{
					bIsFloat = true;
				}
			}
		}
		if (bIsFloat)
		{
			token = NewToken<FloatToken>(_wtof(buffer.c_str()));
		}
		else
		{
			token = NewToken<IntegerToken>(_wtoi(buffer.c_str()));
		}
	}
	
	void Lexer::ReadString(TPtr<Token::Token> &token, TChar stopChar)
	{
		TString buffer;
		while (ch != stopChar)
		{
			buffer.push_back(ch);
			ReadChar();
		}
		token = NewToken<StringToken>(buffer);
	}
	
	void Lexer::ReadIdentifier(TPtr<Token::Token> &token)
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
	
}