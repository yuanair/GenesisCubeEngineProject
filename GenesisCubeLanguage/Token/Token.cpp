#include "Token.h"

using namespace GCL::Token;

std::map<Token::Type, std::string> Token::names = 
{
	{ GCL_Illegal,				"illegal" },
	{ GCL_EOF,					"EOF" },
	{ GCL_Integer,				"integer" },
	{ GCL_Float,				"float" },
	{ GCL_Plus,					"+" },
	{ GCL_Minus,				"-" },
	{ GCL_Multiply,				"*" },
	{ GCL_Divide,				"/" },
	{ GCL_Mod,					"%" },
	{ GCL_LeftParen,			"(" },
	{ GCL_RightParen,			")" },
	{ GCL_Semicolon,			";" },
};

Token::Token()
	: Token(GCL_Illegal, "", TokenPos())
{
	
}

Token::Token(Type type, const std::string& _literal, TokenPos pos)
	: type(type), _literal(_literal), pos(pos)
{

}

Token& Token::operator=(const Token& other)
{
	this->type = other.type;
	this->_literal = other._literal;
	return *this;
}

Token::Type Token::GetType() const
{
	return this->type;
}

std::string Token::GetLiteral() const
{
	return this->_literal;
}

TokenPos Token::GetPos() const
{
	return this->pos;
}

std::string Token::ToTypeString() const
{
	auto it = names.find(this->type);
	if (it != names.end())
	{
		return it->second;
	}
	return "<error token type>";
}

std::string Token::ToJsonString() const
{
	return std::format("{{ \"literal\": \"{}\", \"type\": \"{}\" }}", GetLiteral(), ToTypeString());
}

bool Token::IsEOF() const
{
	return this->type == GCL_EOF;
}

std::string Token::ToString() const
{
	return std::format("[type: {}]\t[name: {}]\t[literal: {}]", (long long)type, ToTypeString(), GetLiteral());
}
