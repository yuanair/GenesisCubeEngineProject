//
// Created by admin on 2023/12/30.
//

#include "Types.h"

namespace GenesisCube::Token
{
	void
	StringToken::GetPrefixExpression(TSharedPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
		expression = NewNode<AST::String>();
	}
	
	Json::Json StringToken::ToJson() const
	{
		Json::Json json;
		json[TEXT("value")] = this->value;
		json[TEXT("type")] = FFormatter::GetTypeName(this);
		return json;
	}
	
	void
	IntegerToken::GetPrefixExpression(TSharedPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
		expression = NewNode<AST::Integer>();
	}
	
	Json::Json IntegerToken::ToJson() const
	{
		Json::Json json;
		json[TEXT("value")] = this->value;
		json[TEXT("type")] = FFormatter::GetTypeName(this);
		return json;
	}
	
	void FloatToken::GetPrefixExpression(TSharedPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
		expression = NewNode<AST::Float>();
	}
	
	Json::Json FloatToken::ToJson() const
	{
		Json::Json json;
		json[TEXT("value")] = this->value;
		json[TEXT("type")] = FFormatter::GetTypeName(this);
		return json;
	}
	
	void CharToken::GetPrefixExpression(TSharedPtr<AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
		expression = NewNode<AST::Char>();
	}
	
	Json::Json CharToken::ToJson() const
	{
		Json::Json json;
		json[TEXT("value")] = ToString();
		json[TEXT("type")] = FFormatter::GetTypeName(this);
		return json;
	}
}