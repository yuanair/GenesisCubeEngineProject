#include "JArray.h"


namespace GenesisCube::JSON
{
	JArray *JArray::Clone() const noexcept
	{
		auto *ptr = new JArray();
		ptr->values = this->values;
		return ptr;
	}
	
	TString JArray::ToString() const noexcept
	{
		if (this->values.empty())
		{
			return TEXT("[ <empty> ]");
		}
		TString buffer;
		buffer.append(TEXT("[ "));
		auto iter = this->values.begin();
		buffer.append(iter->ToString());
		iter++;
		for (; iter != this->values.end(); iter++)
		{
			buffer.append(TEXT(", "));
			buffer.append(iter->ToString());
		}
		buffer.append(TEXT(" ]"));
		return buffer;
	}
}
