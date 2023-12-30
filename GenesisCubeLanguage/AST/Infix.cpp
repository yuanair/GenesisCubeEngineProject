#include "Infix.h"


using namespace GCL::AST;

std::string GCL::AST::Infix::ToJsonString() const
{
	return std::format(R"({{ "left": {}, "Infix operator": "{}", "right": {} }})", 
		this->left->ToJsonString(),
		this->_operator,
		this->right->ToJsonString()
	);
}
