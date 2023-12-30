#include "Parser.h"

#include <utility>

using namespace GCL::Parser;
using namespace GCL::Token;

std::map<Token::Token::Type, int> Parser::precedences =
{
	{Token::Token::Type::GCL_Plus,					Parser::Precedence::Sum},
	{Token::Token::Type::GCL_Minus,					Parser::Precedence::Sum},
	{Token::Token::Type::GCL_Multiply,				Parser::Precedence::Product},
	{Token::Token::Type::GCL_Divide,				Parser::Precedence::Product},
	{Token::Token::Type::GCL_Mod,					Parser::Precedence::Product},
};

std::map<Token::Token::Type, Parser::PrefixParseFn> Parser::PrefixParseFns =
{
	{Token::Token::Type::GCL_Integer,				&Parser::ParseInteger},
	{Token::Token::Type::GCL_LeftParen,				&Parser::ParseGroup},
};

std::map<Token::Token::Type, Parser::InfixParseFn> Parser::InfixParseFns =
{
	{Token::Token::Type::GCL_Plus,					&Parser::ParseInfix},
	{Token::Token::Type::GCL_Minus,					&Parser::ParseInfix},
	{Token::Token::Type::GCL_Multiply,				&Parser::ParseInfix},
	{Token::Token::Type::GCL_Divide,				&Parser::ParseInfix},
	{Token::Token::Type::GCL_Mod,					&Parser::ParseInfix},
};

Parser::Parser()
{

}

Parser::~Parser()
{

}

Parser::Parser(const std::shared_ptr<Lexer::Lexer>& lexer)
	: lexer(lexer)
{
	NextToken();
	NextToken();
}

void Parser::NextToken()
{
	currToken = peekToken;
	peekToken = lexer->NextToken();
}

bool Parser::ExpectPeekToken(Token::Token::Type type)
{
	if (peekToken.GetType() == type)
	{
		NextToken();
		return true;
	}
	else
	{
		PeekError(type);
		return false;
	}
}


void Parser::PeekError(Token::Token::Type type)
{
#pragma message("Error_InvalidTokenType in " __FILE__ "::" __FUNCSIG__)
	NewError(Error::Type::Error_InvalidTokenType, std::format("expectd next token to be [{}], got [{}] instead", Token::Token(type, "", Token::TokenPos()).ToTypeString(), peekToken.ToTypeString()));
}

void Parser::NewError(Error::Type type, std::string message)
{
	errors.emplace_back(type, message, this->currToken.GetPos());
}

int Parser::CurrTokenPrecedence()
{
	auto it = precedences.find(currToken.GetType());
	if (it != precedences.end())
	{
		return it->second;
	}
	return Lowest;
}

int Parser::PeekTokenPrecedence()
{
	auto it = precedences.find(peekToken.GetType());
	if (it != precedences.end())
	{
		return it->second;
	}
	return Lowest;
}

void Parser::NoPrefixParseFnError(Token::Token::Type type)
{
#pragma message("Error_NoPrefixParseFnError in " __FILE__ "::" __FUNCSIG__)
	NewError(Error::Type::Error_NoPrefixParseFnError, std::format("no prefix parse function for [{}]", Token::Token(type, "", Token::TokenPos()).ToTypeString()));
}
