#pragma once

#include "../../GenesisCubeBase/Core/FFormatter.h"

#include "../Lexer/Lexer.h"
#include "../AST/AST.h"


namespace GenesisCube::Parser
{
	// 语法分析类
	class Parser
	{
	public:
		
		// 语法错误
		class Error
		{
		public:
			
			// 语法错误类型枚举
			enum Type
			{
				Error_Illegal = 0,                    // 非法的符号
				Error_NotAsExpected,                  //与预期不符
				Error_NoPrefixParseFnError            // 无效表达式
			};
		
		public:
			
			~Error() {}
			
			Error(Type type, TString message, Token::TokenPos pos)
				: type(type), message(std::move(message)), pos(pos) {}
		
		public:
			
			Type type;
			
			TString message;
			
			Token::TokenPos pos;
			
		};
	
	public:
		
		///
		/// \param lexer 词法分析器
		Parser(TUniquePtr<Lexer::Lexer> &lexer);
		
		~Parser() = default;
	
	public:
		
		///
		/// 解析程序
		/// \param program 程序
		void ParseProgram(TSharedPtr<AST::Program> &program);
		
		///
		/// 解析函数
		/// \param function 函数
		void ParseFunction(TSharedPtr<AST::Function> &function);
		
		///
		/// 解析语句
		/// \param statement 语句
		void ParseStatement(TSharedPtr<AST::Statement> &statement);
		
		///
		/// 解析表达式语句
		/// \param expressionStatement 目标
		void ParseExpressionStatement(TSharedPtr<AST::ExpressionStatement> &expressionStatement);
		
		///
		/// 解析表达式
		/// \param expression 目标
		void ParseExpression(TSharedPtr<AST::Expression> &expression, Token::Token::Precedence precedence);
		
		///
		/// 解析表达式
		/// \param infix 目标
		/// \param left
		void ParseInfix(TSharedPtr<AST::Infix> &infix, const TSharedPtr<AST::Expression> &left);
		
		///
		/// 下一个符号
		///
		void NextToken();
	
	public:
		
		///
		/// \return 错误列表
		[[nodiscard]]
		inline std::list<Error> GetErrors() const { return this->errors; }
		
		///
		/// 新错误
		/// \param type
		/// \param message
		inline void NewError(Error::Type type, const TString &message) noexcept
		{
			errors.emplace_back(type, message, this->currToken->GetPos());
		}
		
		///
		/// 预期一个符号
		/// \tparam T 类型
		/// \return 是否相符
		template<class T>
		inline bool ExpectPeekToken();
		
		///
		/// 下一个符号与预期不符错误
		/// \tparam T 类型
		template<class T>
		inline void PeekTokenError();
		
		///
		/// 前缀表达式解析错误
		inline void NoPrefixParseFnError(const TString &message)
		{
			NewError(Error::Error_NoPrefixParseFnError, message);
		}
		
		///
		/// \tparam T 类型
		/// \return 当前符号是否为T
		template<class T>
		[[nodiscard]]
		inline bool CurrTokenIs() const { return Is<T>(currToken); }
		
		///
		/// \tparam T 类型
		/// \return 下一个符号是否为T
		template<class T>
		[[nodiscard]]
		inline bool PeekTokenIs() const { return Is<T>(peekToken); }
		
		///
		/// \return 当前运算符的优先级
		[[nodiscard]]
		inline auto CurrTokenPrecedence() const { return currToken->GetPrecedence(); }
		
		///
		/// \return 下一个运算符的优先级
		[[nodiscard]]
		inline auto PeekTokenPrecedence() const { return peekToken->GetPrecedence(); }
		
		GCLASS_BODY(Parser)
	
	public:
		
		TUniquePtr<Lexer::Lexer> lexer;
	
	private:
		
		TSharedPtr<Token::Token> currToken;
		
		TSharedPtr<Token::Token> peekToken;
		
		std::list<Error> errors;
		
	};
	
	template<class T>
	inline bool Parser::ExpectPeekToken()
	{
		if (PeekTokenIs<T>())
		{
			NextToken();
			return true;
		}
		else
		{
			PeekTokenError<T>();
			return false;
		}
	}
	
	template<class T>
	inline void Parser::PeekTokenError()
	{
		NewError(
			Error::Type::Error_NotAsExpected, std::format(
				TEXT("expected {}, got {} instead"), FFormatter::GetTypeName<T>(),
				FFormatter::GetTypeName(peekToken.get())));
	}
	
}
