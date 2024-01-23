//
// Created by admin on 2023/12/30.
//

#pragma once

#include "Token.h"

namespace GenesisCube::Token
{
	
	///
	/// 操作符
	///
	class OperatorToken : public Token
	{
	public:
		
		void GetInfixExpression(TSharedPtr<AST::Expression> &expression, const TSharedPtr<AST::Expression> &left,
								Parser::Parser &parser) noexcept override;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return OperatorType; }
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Lowest; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return 0; }
		
		OperatorToken *Clone() const noexcept final
		{
			auto ptr = new OperatorToken;
			ptr->pos = pos;
			return ptr;
		}
		
	};
	
	///
	/// 加号
	///
	class PlusToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return PlusMinus; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("+"); }
		
	};
	
	///
	/// 减号
	///
	class MinusToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return PlusMinus; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("-"); }
		
	};
	
	///
	/// 乘号
	///
	class MultiplyToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return MultiplyDivide; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("*"); }
		
	};
	
	///
	/// 除号
	///
	class DivideToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return MultiplyDivide; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("/"); }
		
	};
	
	///
	/// 求模号
	///
	class ModToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return MultiplyDivide; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("%"); }
		
	};
	
	///
	/// 逗号
	///
	class CommaToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Comma; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT(","); }
		
	};
	
	///
	/// 点
	///
	class PointToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Highest; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("."); }
		
	};
	
	///
	/// 作用域操作符
	///
	class ScopeToken : public OperatorToken
	{
	public:
		
		void GetPrefixExpression(TSharedPtr<AST::Expression> &expression, Parser::Parser &parser) noexcept override;
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Highest; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("::"); }
		
	};
	
}
