#include "Parser.h"

#include "../Token/Tokens.h"

namespace GenesisCube::Parser
{
	
	Parser::Parser(TUniquePtr<Lexer::Lexer> &lexer)
		: lexer(std::move(lexer))
	{
		NextToken();
		NextToken();
	}
	
	void Parser::NextToken()
	{
		currToken = peekToken;
		lexer->NextToken(peekToken);
	}
	
	void Parser::ParseExpression(TSharedPtr<AST::Expression> &expression,
								 Token::Token::Precedence precedence)
	{
		TSharedPtr<AST::Expression> e;
		currToken->GetPrefixExpression(e, *this);
		if (!e)
		{
			NoPrefixParseFnError(
				std::format(TEXT("{} can not prefix parse"), FFormatter::GetTypeName(currToken.get())));
			return;
		}
		while (!PeekTokenIs<Token::SemicolonToken>() && precedence < PeekTokenPrecedence())
		{
			NextToken();
			TSharedPtr<AST::Expression> infix;
			currToken->GetInfixExpression(infix, e, *this);
			if (!infix) break;
			e = infix;
			
		}
		expression = e;
	}
	
	void Parser::ParseInfix(TSharedPtr<AST::Infix> &infix, const TSharedPtr<AST::Expression> &left)
	{
		infix = MakeShared<AST::Infix>();
		infix->token = currToken;
		infix->left = left;
		Token::Token::Precedence precedence = CurrTokenPrecedence();
		NextToken();
		ParseExpression(infix->right, precedence);
	}
	
	void Parser::ParseStatement(TSharedPtr<AST::Statement> &statement)
	{
		TSharedPtr<AST::ExpressionStatement> p;
		ParseExpressionStatement(p);
		statement = p;
	}
	
	void Parser::ParseProgram(TSharedPtr<AST::Program> &program)
	{
		program = MakeShared<AST::Program>();
		while (!CurrTokenIs<Token::EOFToken>())
		{
			TSharedPtr<AST::Function> function;
			ParseFunction(function);
		}
	}
	
	void Parser::ParseExpressionStatement(TSharedPtr<AST::ExpressionStatement> &expressionStatement)
	{
		expressionStatement = MakeShared<AST::ExpressionStatement>();
		expressionStatement->token = currToken;
		ParseExpression(expressionStatement->expression, Token::Token::Lowest);
		while (PeekTokenIs<Token::SemicolonToken>())
		{
			NextToken();
		}
	}
	
	void Parser::ParseFunction(TSharedPtr<AST::Function> &function)
	{
		function = MakeShared<AST::Function>();
		while (!CurrTokenIs<Token::EOFToken>())
		{
			TSharedPtr<AST::Statement> statement;
			ParseStatement(statement);
			function->statements.push_back(statement);
			NextToken();
		}
	}
	
}