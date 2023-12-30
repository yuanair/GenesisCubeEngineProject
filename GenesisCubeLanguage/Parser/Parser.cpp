#include "Parser.h"

#include <utility>

using namespace GenesisCube::Parser;
using namespace GenesisCube::Token;

Parser::Parser()
{

}

Parser::~Parser()
{

}

Parser::Parser(const std::shared_ptr<Lexer::Lexer> &lexer)
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

void Parser::NewError(Error::Type type, TString message)
{
	errors.emplace_back(type, message, this->currToken->GetPos());
}

int Parser::CurrTokenPrecedence()
{
	return currToken->GetPrecedence();
}

int Parser::PeekTokenPrecedence()
{
	return peekToken->GetPrecedence();
}
