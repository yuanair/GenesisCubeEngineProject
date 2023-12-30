#include "Parser.h"


using namespace GCL::Parser;
using namespace GCL::Token;
using namespace GCL::AST;




std::shared_ptr<GCL::AST::Statement> Parser::ParseStatement()
{
	return ParseExpressionStatement();
}