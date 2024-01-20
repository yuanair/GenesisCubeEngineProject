//
// Created by admin on 2023/12/30.
//

#pragma once

#include "../AST/Node.h"
#include "Token.h"
#include "../Parser/Parser.h"


namespace GenesisCube::Token
{
	///
	/// 类型
	///
	class TypeToken : public Token
	{
	public:
		
		[[nodiscard]]
		inline JSON::Json ToJson() const override = 0;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override = 0;
		
		[[nodiscard]]
		inline TString ToString() const noexcept override = 0;
		
		[[nodiscard]]
		inline TypeToken *Clone() const noexcept override = 0;
		
	};
	
	///
	/// 字符串
	///
	class StringToken : public TypeToken
	{
	public:
		
		explicit StringToken(TString value) : value(std::move(value)) {}
	
	public:
		
		void
		GetPrefixExpression(TSharedPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept override;
		
		JSON::Json ToJson() const override;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return StringType; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return value; }
		
		[[nodiscard]]
		inline StringToken *Clone() const noexcept override { return new StringToken(value); }
		
		GCLASS_BODY(StringToken)
	
	public:
		
		TString value;
		
	};
	
	///
	/// 字符
	///
	class CharToken : public TypeToken
	{
	public:
		
		explicit CharToken(TChar value) : value(value) {}
	
	public:
		
		void
		GetPrefixExpression(TSharedPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept override;
		
		JSON::Json ToJson() const override;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return StringType; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TString({value}); }
		
		[[nodiscard]]
		inline CharToken *Clone() const noexcept override { return new CharToken(value); }
		
		GCLASS_BODY(CharToken)
	
	public:
		
		TChar value;
		
	};
	
	///
	/// 整数
	///
	class IntegerToken : public TypeToken
	{
	public:
		
		explicit IntegerToken(int32_t value) : value(value) {}
	
	public:
		
		void
		GetPrefixExpression(TSharedPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept override;
		
		JSON::Json ToJson() const override;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return NumberType; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return ToTString(value); }
		
		[[nodiscard]]
		inline IntegerToken *Clone() const noexcept override { return new IntegerToken(value); }
		
		GCLASS_BODY(IntegerToken)
	
	public:
		
		int32_t value;
		
	};
	
	///
	/// 浮点数
	///
	class FloatToken : public TypeToken
	{
	public:
		
		explicit FloatToken(double_t value) : value(value) {}
	
	public:
		
		void
		GetPrefixExpression(TSharedPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept override;
		
		JSON::Json ToJson() const override;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return NumberType; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return ToTString(value); }
		
		[[nodiscard]]
		inline FloatToken *Clone() const noexcept override { return new FloatToken(value); }
		
		GCLASS_BODY(FloatToken)
	
	public:
		
		double_t value;
		
	};
	
}
