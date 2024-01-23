//
// Created by admin on 2023/12/19.
//

#include "GObject.h"
#include "../Core/FFormatter.h"

namespace GenesisCube
{
	
	TString GObject::ToString() const noexcept
	{
		return std::format(TEXT("{}(0x{:016X})"), FFormatter::GetTypeName(this), (uintptr_t) this);
	}
	
} // GenesisCube