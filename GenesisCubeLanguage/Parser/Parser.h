#pragma once

#include "../Lexer/Lexer.h"


namespace GenesisCube::Parser
{
	// 语法分析类
	class Parser
	{
	public:
		
		// 优先级
		enum Precedence : int
		{
			Lowest = 0,                // 最低优先级
			Sum,                    // +与-优先级
			Product,                // *与/优先级
		};
		
		// 语法错误
		class Error
		{
		public:
			
			// 语法错误类型枚举
			enum Type
			{
				Error_Illegal = 0,                    // 非法的符号
				Error_InvalidTokenType,                // 无效的符号类型
				Error_NoPrefixParseFnError            // 无效表达式
			};
		
		public:
			
			Error() : Error(Error_Illegal, TEXT(""), 0LL) {}
			
			~Error() {}
			
			Error(Type type, TString message, Token::TokenPos pos)
				: type(type), message(message), pos(pos) {}
		
		public:
			
			Type type;
			
			TString message;
			
			Token::TokenPos pos;
			
		};
	
	public:
		
		Parser();
		
		~Parser();
		
		// lexer - 词法分析器指针
		Parser(const std::shared_ptr<Lexer::Lexer> &lexer);
	
	public:
		
		///
		/// 下一个
		///
		void NextToken();
	
	private:
		
		template<class T>
		bool ExpectPeekToken();
		
		[[nodiscard]]
		std::list<Error> GetErrors() const { return this->errors; }
		
		void NewError(Error::Type type, TString message);
		
		template<class T>
		void PeekError();
		
		int CurrTokenPrecedence();
		
		int PeekTokenPrecedence();
	
	private:
		
		std::shared_ptr<Lexer::Lexer> lexer;
		
		TPtr<Token::Token> currToken;
		
		TPtr<Token::Token> peekToken;
		
		std::list<Error> errors;
		
	};
	
	template<class T>
	bool Parser::ExpectPeekToken()
	{
		if (peekToken->Is<T>())//peekToken->GetType() == type)
		{
			NextToken();
			return true;
		}
		else
		{
			PeekError<T>();
			return false;
		}
	}
	
	template<class T>
	void Parser::PeekError()
	{
		NewError(
			Error::Type::Error_InvalidTokenType, std::format(
				TEXT("Should not be [{}]"), peekToken->GetName()));
	}
	
}
