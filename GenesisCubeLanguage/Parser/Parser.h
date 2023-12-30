#pragma once
#include "../Lexer/Lexer.h"
#include "../AST/AST.h"


namespace GCL::Parser
{
	// 语法分析类
	class Parser
	{
	public:

		// 优先级
		enum Precedence : int
		{
			Lowest = 0,				// 最低优先级
			Sum,					// +与-优先级
			Product,				// *与/优先级
		};

		// 语法错误
		class Error
		{
		public:

			// 语法错误类型枚举
			enum Type
			{
				Error_Illegal = 0,					// 非法的符号
				Error_InvalidTokenType,				// 无效的符号类型
				Error_NoPrefixParseFnError			// 无效表达式
			};

		public:

			Error() : Error(Error_Illegal, "", 0LL) {}
			~Error() {}

			Error(Type type, std::string message, Token::TokenPos pos)
				: type(type), message(message), pos(pos) {}

		public:

			Type type;
			
			std::string message;

			Token::TokenPos pos;

		};

		// 前缀表达式构建函数原型定义
		typedef std::shared_ptr<GCL::AST::Expression> (Parser::*PrefixParseFn)(void);

		// 中缀表达式构建函数原型定义
		typedef std::shared_ptr<GCL::AST::Expression> (Parser::*InfixParseFn)(const std::shared_ptr<GCL::AST::Expression>&);

	public:

		Parser();
		~Parser();

		// lexer - 词法分析器指针
		Parser(const std::shared_ptr<Lexer::Lexer>& lexer);

	public:

		void NextToken();

		bool ExpectPeekToken(Token::Token::Type type);


		std::list<Error> GetErrors() const { return this->errors; }

		void NewError(Error::Type type, std::string message);

		void PeekError(Token::Token::Type type);

		void NoPrefixParseFnError(Token::Token::Type type);


		int CurrTokenPrecedence();
		int PeekTokenPrecedence();


		std::shared_ptr<GCL::AST::Expression> ParseExpression(int precedence);

		std::shared_ptr<GCL::AST::Program> ParseProgram();

		std::shared_ptr<GCL::AST::Statement> ParseStatement();

		std::shared_ptr<GCL::AST::ExpressionStatement> ParseExpressionStatement();

		// prefix

		std::shared_ptr<GCL::AST::Expression> ParseInteger();

		std::shared_ptr<GCL::AST::Expression> ParseGroup();

		// infix

		std::shared_ptr<GCL::AST::Expression> ParseInfix(const std::shared_ptr<GCL::AST::Expression>& left);

	private:

		static std::map<Token::Token::Type, int> precedences;

		static std::map<Token::Token::Type, Parser::PrefixParseFn> PrefixParseFns;

		static std::map<Token::Token::Type, Parser::InfixParseFn> InfixParseFns;

	private:

		std::shared_ptr<Lexer::Lexer> lexer;

		Token::Token currToken;

		Token::Token peekToken;

		std::list<Error> errors;

	};

}
