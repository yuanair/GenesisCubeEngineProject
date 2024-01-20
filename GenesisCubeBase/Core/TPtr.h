#pragma once

#include "Header.h"
#include "../Exception/Exception.h"

namespace GenesisCube
{
	
	template<class T>
	using TComPtr = Microsoft::WRL::ComPtr<T>;
	
	template<class T>
	using TSharedPtr = std::shared_ptr<T>;
	
	template<class T>
	using TUniquePtr = std::unique_ptr<T>;
	
	template<class T>
	using TWeakPtr = std::weak_ptr<T>;
	
	template<class T, class... Args>
	TSharedPtr<T> MakeShared(Args &&... args)
	{
		return std::make_shared<T>(args...);
	}
	
	template<class T, class... Args>
	TUniquePtr<T> MakeUnique(Args &&... args)
	{
		return std::make_unique<T>(args...);
	}
	
	template<class T, class U>
	TComPtr<T> PtrCast(const TComPtr<U> &ptr)
	{
		TComPtr<T> result;
		ptr.As(result);
		return result;
	}
	
	template<class T, class U>
	TSharedPtr<T> PtrCast(const TSharedPtr<U> &ptr)
	{
		return std::dynamic_pointer_cast<T>(ptr);
	}
	
	template<class T, class U>
	TSharedPtr<T> PtrCast(TSharedPtr<U> &&ptr)
	{
		return std::dynamic_pointer_cast<T>(std::move(ptr));
	}
	
	template<class T, class Ptr>
	bool Is(Ptr ptr)
	{
		if (ptr == nullptr) return typeid(std::nullptr_t) == typeid(T);
		return typeid(*ptr) == typeid(T);
	}
	
	
}


