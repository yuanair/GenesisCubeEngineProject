//
// Created by admin on 2023/12/30.
//

#pragma once

#include "Brackets.h"
#include "Operators.h"
#include "Types.h"

namespace GenesisCube::Token
{
	
	///
	/// 非法的符号
	///
	class IllegalToken : public Token
	{
	public:
		
		explicit IllegalToken(TString value) : value(std::move(value)) {}
	
	public:
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return IllegalType; }
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Illegal"); }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return value; }
		
		[[nodiscard]]
		inline IllegalToken *Clone() const noexcept override { return new IllegalToken(value); }
	
	public:
		
		TString value;
		
	};
	
	///
	/// 标识符
	///
	class IdentifierToken : public Token
	{
	public:
		
		explicit IdentifierToken(TString value) : value(std::move(value)) {}
	
	public:
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return IdentifierType; }
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Identifier"); }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return value; }
		
		[[nodiscard]]
		inline IdentifierToken *Clone() const noexcept override { return new IdentifierToken(value); }
	
	public:
		
		TString value;
		
	};
	
	///
	/// 结束符
	///
	class EOFToken : public Token
	{
	public:
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return IllegalType; }
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("EOF"); }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("EOF"); }
		
		[[nodiscard]]
		inline EOFToken *Clone() const noexcept override { return new EOFToken(); }
		
	};
	
	///
	/// 分号
	///
	class SemicolonToken : public Token
	{
	public:
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return SemicolonType; }
		
		[[nodiscard]]
		inline TString GetName() const noexcept override { return TEXT("Semicolon"); }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT(";"); }
		
		[[nodiscard]]
		inline SemicolonToken *Clone() const noexcept override { return new SemicolonToken(); }
		
	};
	
} // GenesisCube
