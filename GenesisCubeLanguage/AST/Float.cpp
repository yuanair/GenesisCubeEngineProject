#include "Float.h"

using namespace GCL::AST;

std::string Float::ToJsonString() const
{
	return std::format("{{ \"float\": {}, \"token\": \"{}\", \"type\": \"{}\" }}", value, GetToken().ToJsonString(), ToTypeString());
}

std::string GCL::AST::Double::ToJsonString() const
{
	return std::format("{{ \"double\": {}, \"token\": \"{}\", \"type\": \"{}\" }}", value, GetToken().ToJsonString(), ToTypeString());
}
