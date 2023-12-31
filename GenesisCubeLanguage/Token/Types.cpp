//
// Created by admin on 2023/12/30.
//

#include "Types.h"

namespace GenesisCube::Token
{
	void StringToken::GetPrefixExpression(TPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
		expression = NewNode<AST::String>();
	}
	
	JSON::Json StringToken::ToJson() const
	{
		JSON::Json json;
		json[TEXT("value")] = this->value;
		json[TEXT("type")] = GetName();
		return json;
	}
	
	void IntegerToken::GetPrefixExpression(TPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
		expression = NewNode<AST::Integer>();
	}
	
	JSON::Json IntegerToken::ToJson() const
	{
		JSON::Json json;
		json[TEXT("value")] = this->value;
		json[TEXT("type")] = GetName();
		return json;
	}
	
	void FloatToken::GetPrefixExpression(TPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
		expression = NewNode<AST::Float>();
	}
	
	JSON::Json FloatToken::ToJson() const
	{
		JSON::Json json;
		json[TEXT("value")] = this->value;
		json[TEXT("type")] = GetName();
		return json;
	}
	
}