#include "Integer.h"


using namespace GCL::AST;

std::string Integer::ToJsonString() const
{
	return std::format("{{ \"integer\": {} }}", value);
}
