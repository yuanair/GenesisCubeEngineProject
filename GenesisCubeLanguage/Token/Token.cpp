#include "Token.h"
#include "Tokens.h"

namespace GenesisCube::Token
{
	
	Token::Token()
		: Token(TokenPos())
	{
	
	}
	
	Token::Token(TokenPos pos)
		: pos(pos)
	{
	
	}
	
	TokenPos Token::GetPos() const
	{
		return this->pos;
	}
	
	bool Token::IsEOF() const
	{
		return typeid(*this) == typeid(EOFToken);
	}
	
	Json::Json Token::ToJson() const
	{
		Json::Json json;
		json[TEXT("value")] = ToString();
		json[TEXT("type")] = FFormatter::GetTypeName(this);
		return json;
	}
	
}