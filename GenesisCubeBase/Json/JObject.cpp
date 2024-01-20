#include "JObject.h"
#include "../Core/FFormatter.h"

namespace GenesisCube
{
	
	JSON::JObject *JSON::JObject::Clone() const noexcept
	{
		auto *ptr = new JSON::JObject();
		ptr->values = this->values;
		return ptr;
	}
	
	TString JSON::JObject::ToString() const noexcept
	{
		if (this->values.empty())
		{
			return TEXT("{ }");
		}
		TString buffer;
		buffer.append(TEXT("{ "));
		auto iter = this->values.begin();
		buffer.append(TEXT("\""));
		buffer.append(FFormatter::ToShowString(iter->first));
		buffer.append(TEXT("\": "));
		buffer.append(iter->second.ToString());
		iter++;
		for (; iter != this->values.end(); iter++)
		{
			buffer.append(TEXT(", "));
			buffer.append(TEXT("\""));
			buffer.append(FFormatter::ToShowString(iter->first));
			buffer.append(TEXT("\": "));
			buffer.append(iter->second.ToString());
		}
		buffer.append(TEXT(" }"));
		return buffer;
	}
	
}