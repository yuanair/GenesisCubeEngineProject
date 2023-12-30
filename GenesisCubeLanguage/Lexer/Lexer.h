#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

#include "../Token/Token.h"


namespace GenesisCube::Lexer
{
	// 词法分析器
	class Lexer
	{
	public:
		
		// 词法错误
		class Error
		{
		public:
			
			// 语法错误类型枚举
			enum Type : int32_t
			{
				Error_Illegal = 0,                    // 非法的符号
				Error_ErrorNumber,                // 错误数字
			};
		
		public:
			
			Error(Type type, TString message, Token::TokenPos pos)
				: type(type), message(std::move(message)), pos(pos) {}
			
			~Error() = default;
		
		public:
			
			Type type;
			
			TString message;
			
			Token::TokenPos pos;
			
		};
	
	public:
		
		Lexer();
		
		~Lexer() = default;
		
		// file - 文件
		Lexer(const TString &file);
	
	public:
		
		// 下一个符号
		void NextToken(TPtr<Token::Token> &token);
		
		// 获取位置
		[[nodiscard]]
		Token::TokenPos GetTokenPos() const;
		
		[[nodiscard]]
		inline std::list<Error> GetErrors() const { return this->errors; }
	
	private:
		
		void SkipWhiteSpace();
		
		void ReadChar();
		
		TChar PeekChar();
		
		void UnreadChar();
		
		template<class T, class... Args>
		T *NewToken(Args... args) const;
		
		template<class T, class... Args>
		T *NewToken(Args... args);
		
		void ReadNumber(TPtr<Token::Token> &token);
		
		void ReadString(TPtr<Token::Token> &token, TChar stopChar);
		
		void ReadIdentifier(TPtr<Token::Token> &token);
		
		void NewError(Error::Type type, const TString &message);
	
	private:
		
		TString input;
		
		TChar ch;
		
		size_t pos;
		
		size_t nextPos;
		
		Token::TokenPos tokenPos;
		
		std::list<Error> errors;
		
	};
	
	template<class T, class... Args>
	T *Lexer::NewToken(Args... args) const
	{
		auto *ptr = new T(args...);
		ptr->pos = tokenPos;
		return ptr;
	}
	
	template<class T, class... Args>
	T *Lexer::NewToken(Args... args)
	{
		auto *ptr = new T(args...);
		ptr->pos = tokenPos;
		return ptr;
	}
	
}

