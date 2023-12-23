#include "GString.h"
#include "../Core/FFormatter.h"

namespace GenesisCubeEngine
{
	
	TString GString::ToString() const noexcept
	{
		return TEXT("\"") + FFormatter::ToShowString(this->str) + TEXT("\"");
	}
	
}
