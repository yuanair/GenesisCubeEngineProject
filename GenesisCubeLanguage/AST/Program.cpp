#include "Program.h"

using namespace GCL::AST;

std::string GCL::AST::Program::ToJsonString() const
{
	std::string jsonBuffer;
	jsonBuffer += "{\n";
	jsonBuffer += "\"type\": \"";
	jsonBuffer += this->ToTypeString();
	jsonBuffer += "\", \n\"statements\": \n[\n";
	for (auto& it : this->statements)
	{
		jsonBuffer += it->ToJsonString();
		jsonBuffer += ", \n";
	}
	jsonBuffer += "]\n}";
	return jsonBuffer;
}
