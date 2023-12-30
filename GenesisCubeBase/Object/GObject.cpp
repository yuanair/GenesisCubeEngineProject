//
// Created by admin on 2023/12/19.
//

#include "GObject.h"
#include "../Core/FFormatter.h"
#include "../Exception/Exception.h"

namespace GenesisCube
{
	
	GObject::GObject() noexcept
		: ref(0)
	{
	
	}
	
	GObject::~GObject() noexcept(false)
	{
		if (this->ref != 0)
		{
			throw ENotReleasedException(__FUNCSIG__ TEXT(":: GetRef() should be zero"));
		}
	}
	
	size_t GObject::AddRef() noexcept
	{
		return ++this->ref;
	}
	
	size_t GObject::Release() noexcept
	{
		if (--this->ref == 0)
		{
			delete this;
			return 0;
		}
		return this->ref;
	}
	
	TString GObject::ToString() const noexcept
	{
#ifdef UNICODE
		return std::format(TEXT("{}(0x{:016X})"), FFormatter::StringToWString(typeid(*this).name()), (uintptr_t) this);
#else
		return std::format(TEXT("{}(0x{:016X})"), typeid(*this).name(), (uintptr_t) this);
#endif
	}
	
} // GenesisCube