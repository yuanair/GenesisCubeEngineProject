//
// Created by admin on 2023/12/30.
//

#pragma once

#include "../AST/Node.h"
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
		inline Type GetType() const noexcept override = 0;
		
		[[nodiscard]]
		inline TString GetName() const noexcept override = 0;
		
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
		
		void GetPrefix(TPtr<AST::Expression> &expression) noexcept override;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return StringType; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return value; }
		
		[[nodiscard]]
		inline StringToken *Clone() const noexcept override { return new StringToken(value); }
		
		GCLASS_BODY(String)
	
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
		
		void GetPrefix(TPtr<AST::Expression> &expression) noexcept override;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return NumberType; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return ToTString(value); }
		
		[[nodiscard]]
		inline IntegerToken *Clone() const noexcept override { return new IntegerToken(value); }
		
		GCLASS_BODY(Integer)
	
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
		
		void GetPrefix(TPtr<AST::Expression> &expression) noexcept override;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return NumberType; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return ToTString(value); }
		
		[[nodiscard]]
		inline FloatToken *Clone() const noexcept override { return new FloatToken(value); }
		
		GCLASS_BODY(Float)
	
	public:
		
		double_t value;
		
	};
	
}
