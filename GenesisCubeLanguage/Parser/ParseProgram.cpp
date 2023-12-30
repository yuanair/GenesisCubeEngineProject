#include "Parser.h"


using namespace GCL::Parser;
using namespace GCL::Token;
using namespace GCL::AST;



std::shared_ptr<GCL::AST::Program> Parser::ParseProgram()
{
	std::shared_ptr<Program> s(new Program());

	while (currToken.GetType() != Token::Token::GCL_EOF)
	{
		auto stmt = ParseStatement();
		if (stmt)
		{
			s->statements.push_back(stmt);
		}
		NextToken();
	}
	return s;
}