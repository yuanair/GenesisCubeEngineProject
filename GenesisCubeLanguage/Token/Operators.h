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
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return OperatorType; }
		
		[[nodiscard]]
		inline TString GetName() const noexcept override = 0;
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override = 0;
		
		[[nodiscard]]
		inline TString ToString() const noexcept override = 0;
		
		[[nodiscard]]
		inline OperatorToken *Clone() const noexcept override = 0;
		
	};
	
	///
	/// 加号
	///
	class PlusToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Plus"); }
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Sum; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("+"); }
		
		[[nodiscard]]
		inline PlusToken *Clone() const noexcept override { return new PlusToken(); }
		
	};
	
	///
	/// 减号
	///
	class MinusToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Minus"); }
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Sum; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("-"); }
		
		[[nodiscard]]
		inline MinusToken *Clone() const noexcept override { return new MinusToken(); }
		
	};
	
	///
	/// 乘号
	///
	class MultiplyToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Multiply"); }
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Product; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("*"); }
		
		[[nodiscard]]
		inline MultiplyToken *Clone() const noexcept override { return new MultiplyToken(); }
		
	};
	
	///
	/// 除号
	///
	class DivideToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Divide"); }
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Product; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("/"); }
		
		[[nodiscard]]
		inline DivideToken *Clone() const noexcept override { return new DivideToken(); }
		
	};
	
	///
	/// 求模号
	///
	class ModToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Mod"); }
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Product; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("%"); }
		
		[[nodiscard]]
		inline ModToken *Clone() const noexcept override { return new ModToken(); }
		
	};
	
}
