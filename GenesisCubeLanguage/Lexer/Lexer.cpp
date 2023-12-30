#include "Lexer.h"

using namespace GCL::Lexer;
using namespace GCL::Token;

Lexer::Lexer()
	: ch('\0'), pos(0LL), nextPos(0LL), tokenPos()
{

}

Lexer::Lexer(const std::string& file)
	: ch('\0'), pos(0LL), nextPos(0LL), tokenPos(0LL, 1LL)
{

	std::ifstream ifs(file);
	if (!ifs.good())
	{
		std::cerr << "file not found: " << file << std::endl;
		return;
	}

	std::ostringstream oss;
	oss << ifs.rdbuf();

	input = oss.str();
}

Token Lexer::NextToken()
{
	ReadChar();
	SkipWhiteSpace();
	switch (ch)
	{
	case '+':
	{
		return NewToken(Token::Token::Type::GCL_Plus, "+");
	}
	case '-':
	{
		return NewToken(Token::Token::Type::GCL_Minus, "-");
	}
	case '*':
	{
		return NewToken(Token::Token::Type::GCL_Multiply, "*");
	}
	case '/':
	{
		return NewToken(Token::Token::Type::GCL_Divide, "/");
	}
	case '(':
	{
		return NewToken(Token::Token::Type::GCL_LeftParen, "(");
	}
	case ')':
	{
		return NewToken(Token::Token::Type::GCL_RightParen, ")");
	}
	case ';':
	{
		return NewToken(Token::Token::Type::GCL_Semicolon, ";");
	}
	case '\0':
	{
		return NewToken(Token::Token::Type::GCL_EOF, "EOF");
	}
	default:
	{
		if (ch >= '0' && ch <= '9')
		{
			std::string buffer = ReadNumber();
			UnreadChar();
			return NewToken(Token::Token::Type::GCL_Integer, buffer);
		}
		else
		{
			std::string buffer;
			buffer += ch;
			return NewToken(Token::Token::Type::GCL_Illegal, buffer);
		}
	}
	}
}

TokenPos GCL::Lexer::Lexer::GetTokenPos() const
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
		if (ch == '\n')
		{
			tokenPos.line++;
			tokenPos.ch = 0LL;
		}
		tokenPos.ch++;
	}
	pos = nextPos;
	nextPos++;
}

void Lexer::UnreadChar()
{
	nextPos = pos;
	pos--;
}

Token Lexer::NewToken(Token::Token::Type type, const std::string& _literal) const
{
	return Token::Token(type, _literal, this->tokenPos);
}

std::string Lexer::ReadNumber()
{
	size_t startPos = pos;
	while (ch >= '0' && ch <= '9')
	{
		ReadChar();
	}
	return input.substr(startPos, pos - startPos);
}

