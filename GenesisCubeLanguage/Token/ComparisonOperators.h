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
		
	};
	
} // GenesisCube
