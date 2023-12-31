#include "Parser.h"

#include <utility>

using namespace GenesisCube::Parser;
using namespace GenesisCube::Token;

Parser::Parser(const TPtr <Lexer::Lexer> &lexer)
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
