#pragma once

#include "Header.h"
#include "../Exception/Exception.h"

namespace GenesisCube
{
	
	template<class T>
	using TPtr = std::shared_ptr<T>;
	
	template<class T, class... Args>
	TPtr<T> MakePtr(Args... args)
	{
		return std::make_shared<T>(args...);
	}
	
	template<class T, class U>
	TPtr<T> CastPtr(TPtr<U> ptr)
	{
		return std::dynamic_pointer_cast<T>(ptr);
	}
	
	template<class T, class U>
	bool Is(TPtr<U> ptr)
	{
		return CastPtr<T>(ptr) != nullptr;
	}
	
	
}


