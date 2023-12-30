#include "Node.h"

using namespace GCL::AST;

std::map<Node::Type, std::string> Node::names =
{
	{ Node_Program,					"Program" },
	{ Node_Integer,					"Integer" },
	{ Node_Float,					"Float" },
	{ Node_Infix,					"Infix" },
	{ Node_ExpressionStatement,		"ExpressionStatement" },
};

std::string Node::ToTypeString() const
{
	auto it = names.find(this->type);
	if (it != names.end())
	{
		return it->second;
	}
	return "<error node type>";
}


std::string Node::ToJsonString() const
{
	return std::format("{{ \"token\": {}, \"type\": \"{}\" }}", GetToken().ToJsonString(), ToTypeString());
}