//
// Created by admin on 2023/12/30.
//

#pragma once

#include "Token.h"


namespace GenesisCube::Token
{
	///
	/// 类型
	///
	class TypeToken : public Token
	{
	public:
		
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
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return StringType; }
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("String"); }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return value; }
		
		[[nodiscard]]
		inline StringToken *Clone() const noexcept override { return new StringToken(value); }
	
	public:
		
		TString value;
		
	};
	
	///
	/// 整数
	///
	class IntegerToken : public TypeToken
	{
	public:
		
		explicit IntegerToken(int32_t value) : value(value) {}
	
	public:
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return NumberType; }
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Integer"); }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return ToTString(value); }
		
		[[nodiscard]]
		inline IntegerToken *Clone() const noexcept override { return new IntegerToken(value); }
	
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
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return NumberType; }
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Float"); }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return ToTString(value); }
		
		[[nodiscard]]
		inline FloatToken *Clone() const noexcept override { return new FloatToken(value); }
	
	public:
		
		double_t value;
		
	};
	
}
