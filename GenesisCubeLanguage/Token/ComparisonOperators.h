//
// Created by admin on 2023/12/31.
//

#pragma once

#include "Operators.h"

namespace GenesisCube::Token
{
	
	///
	/// 等于运算符
	///
	class EqualToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Comparison; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("=="); }
	
	GCLASS_BODY(EqualToken)
	};
	
	///
	/// 不等于运算符
	///
	class UnequalToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Comparison; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("!="); }
	
	GCLASS_BODY(UnequalToken)
	};
	
	///
	/// 小于运算符
	///
	class LessThanToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return GreaterLess; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("<"); }
	
	GCLASS_BODY(LessThanToken)
	};
	
	///
	/// 大于运算符
	///
	class GreaterThanToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return GreaterLess; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT(">"); }
	
	GCLASS_BODY(GreaterToken)
	};
	
	///
	/// 小于或等于运算符
	///
	class LessThanEqualToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return GreaterLess; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("<="); }
	
	GCLASS_BODY(LessThanEqualToken)
	};
	
	///
	/// 大于或等于运算符
	///
	class GreaterThanEqualToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return GreaterLess; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT(">="); }
	
	GCLASS_BODY(GreaterThanEqualToken)
	};
	
} // GenesisCube
