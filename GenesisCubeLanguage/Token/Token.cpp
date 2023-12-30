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
	
	JSON::Json Token::ToJson() const
	{
		JSON::Json json;
		json[TEXT("value")] = ToString();
		json[TEXT("type")] = GetName();
		return json;
	}
	
}