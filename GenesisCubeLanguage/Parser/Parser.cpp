#include "Parser.h"

#include "../Token/Tokens.h"
#include "../AST/Infix.h"

namespace GenesisCube::Parser
{
	
	Parser::Parser(const TPtr<Lexer::Lexer> &lexer)
		: lexer(lexer)
	{
		NextToken();
		NextToken();
	}
	
	void Parser::NextToken()
	{
		currToken = peekToken;
		lexer->NextToken(peekToken);
	}
	
	void Parser::ParseExpression(TPtr<AST::Expression> &expression,
								 Token::Token::Precedence precedence)
	{
		TPtr<AST::Expression> e;
		currToken->GetPrefixExpression(e, *this);
		if (!e)
		{
			NoPrefixParseFnError(std::format(TEXT("{} can not prefix parse"), currToken->GetName()));
			return;
		}
		while (!PeekTokenIs<Token::SemicolonToken>() && precedence < PeekTokenPrecedence())
		{
			NextToken();
			TPtr<AST::Expression> infix;
			currToken->GetInfixExpression(infix, e, *this);
			if (!infix) break;
			e = infix;
			
		}
		expression = e;
	}
	
	void Parser::ParseInfix(TPtr<AST::Infix> &infix, const TPtr<AST::Expression> &left)
	{
		infix = MakePtr<AST::Infix>();
		infix->token = currToken;
		infix->left = left;
		Token::Token::Precedence precedence = CurrTokenPrecedence();
		NextToken();
		ParseExpression(infix->right, precedence);
	}
	
	void Parser::ParseStatement(TPtr<AST::Statement> &statement)
	{
		TPtr<AST::ExpressionStatement> p;
		ParseExpressionStatement(p);
		statement = p;
	}
	
	void Parser::ParseProgram(TPtr<AST::Program> &program)
	{
		program = MakePtr<AST::Program>();
		while (!CurrTokenIs<Token::EOFToken>())
		{
			TPtr<AST::Function> function;
			ParseFunction(function);
		}
	}
	
	void Parser::ParseExpressionStatement(TPtr<AST::ExpressionStatement> &expressionStatement)
	{
		expressionStatement = MakePtr<AST::ExpressionStatement>();
		expressionStatement->token = currToken;
		ParseExpression(expressionStatement->expression, Token::Token::Lowest);
		while (PeekTokenIs<Token::SemicolonToken>())
		{
			NextToken();
		}
	}
	
	void Parser::ParseFunction(TPtr<AST::Function> &function)
	{
		function = MakePtr<AST::Function>();
		while (!CurrTokenIs<Token::EOFToken>())
		{
			TPtr<AST::Statement> statement;
			ParseStatement(statement);
			function->statements.push_back(statement);
			NextToken();
		}
	}
	
}