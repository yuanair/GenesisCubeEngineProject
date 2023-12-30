//
// Created by admin on 2023/12/30.
//

#pragma once

#include "Token.h"

namespace GenesisCube::Token
{
	///
	/// 括号
	///
	class BracketToken : public Token
	{
	public:
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return BracketType; }
		
		[[nodiscard]]
		inline BracketToken *Clone() const noexcept override = 0;
		
	};
	
	///
	/// 左圆括号
	///
	class LeftParenToken : public BracketToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("LeftParen"); }
		
		[[nodiscard]]
		Precedence GetPrecedence() const noexcept override { return Lowest; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("("); }
		
		[[nodiscard]]
		inline LeftParenToken *Clone() const noexcept override { return new LeftParenToken(); }
		
	};
	
	///
	/// 右圆括号
	///
	class RightParenToken : public BracketToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("RightParen"); }
		
		[[nodiscard]]
		Precedence GetPrecedence() const noexcept override { return Lowest; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT(")"); }
		
		[[nodiscard]]
		inline RightParenToken *Clone() const noexcept override { return new RightParenToken(); }
		
	};
	
	///
	/// 左方括号
	///
	class LeftBracketToken : public BracketToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("LeftBracket"); }
		
		[[nodiscard]]
		Precedence GetPrecedence() const noexcept override { return Lowest; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("["); }
		
		[[nodiscard]]
		inline LeftBracketToken *Clone() const noexcept override { return new LeftBracketToken(); }
		
	};
	
	///
	/// 右方括号
	///
	class RightBracketToken : public BracketToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("RightBracket"); }
		
		[[nodiscard]]
		Precedence GetPrecedence() const noexcept override { return Lowest; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("]"); }
		
		[[nodiscard]]
		inline RightBracketToken *Clone() const noexcept override { return new RightBracketToken(); }
		
	};
	
	///
	/// 左花括号
	///
	class LeftBraceToken : public BracketToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("LeftBrace"); }
		
		[[nodiscard]]
		Precedence GetPrecedence() const noexcept override { return Lowest; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("{"); }
		
		[[nodiscard]]
		inline LeftBraceToken *Clone() const noexcept override { return new LeftBraceToken(); }
		
	};
	
	///
	/// 右花括号
	///
	class RightBraceToken : public BracketToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("RightBrace"); }
		
		[[nodiscard]]
		Precedence GetPrecedence() const noexcept override { return Lowest; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("}"); }
		
		[[nodiscard]]
		inline RightBraceToken *Clone() const noexcept override { return new RightBraceToken(); }
		
	};
	
}
