#include "Object.h"

using namespace GCL::Object;

std::map<Object::Type, std::string> Object::names =
{
	{Object_Error, "error"},
	{Object_Integer, "integer"},
	{Object_Float, "float"},
	{Object_Bool, "bool"},
	{Object_Char, "char"},
};

Object::Type Object::GetType() const
{
	return this->type;
}

std::string Object::ToTypeString() const
{
	auto it = names.find(this->type);
	if (it != names.end())
	{
		return it->second;
	}
	return "<error object type>";
}
