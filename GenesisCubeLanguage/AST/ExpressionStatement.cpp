#include "ExpressionStatement.h"


using namespace GCL::AST;

std::string GCL::AST::ExpressionStatement::ToJsonString() const
{
    return std::format("{{ \"type\": \"{}\", \"expression\": {} }}", ToTypeString(), this->expression ? this->expression->ToJsonString() : "null");
}
