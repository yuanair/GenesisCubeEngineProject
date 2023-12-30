#include "GString.h"
#include "../Core/FFormatter.h"

namespace GenesisCube
{
	
	TString GString::ToString() const noexcept
	{
		return TEXT("\"") + FFormatter::ToShowString(this->str) + TEXT("\"");
	}
	
}
