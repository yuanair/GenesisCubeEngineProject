#pragma once

#include "Header.h"
#include "../Exception/Exception.h"

namespace GenesisCubeEngine
{
	
	///
	/// 指针模板
	///
	/// \tparam T 必须为GObject或其子类
	template<class T>
	class TPtr
	{
	public:
		
		inline TPtr() noexcept;
		
		inline TPtr(nullptr_t _other) noexcept;
		
		inline TPtr(const TPtr &_other) noexcept;
		
		inline TPtr(T *_ptr) noexcept;
		
		inline ~TPtr() noexcept;
	
	public:
		
		///
		/// 赋值
		///
		inline TPtr &operator=(const TPtr &_other) noexcept;
		
		///
		/// 相等运算符
		///
		inline bool operator==(const TPtr &_other) const noexcept;
		
		///
		/// 不相等运算符
		///
		inline bool operator!=(const TPtr &_other) const noexcept;
		
		///
		/// 指针
		///
		///
		inline T *operator->()
		{
			if (this->ptr == nullptr) throw ENullptrException(TEXT(__FUNCSIG__) ":: nullptr");
			return this->ptr;
		}
		
		///
		/// 指针
		///
		///
		inline T *operator->() const
		{
			if (this->ptr == nullptr)
				throw ENullptrException(
					TEXT(__FUNCSIG__) ":: nullptr"
				);
			return this->ptr;
		}
		
		///
		/// bool
		///
		inline operator bool() noexcept { return this->ptr != nullptr; }
	
	public:
		
		///
		/// 重置
		///
		///
		inline size_t Reset() noexcept;
		
		///
		/// 类型
		///
		///
		inline const type_info &TypeId() const noexcept;
		
		///
		/// 类型转换
		///
		template<class U>
		inline U *Cast() const noexcept;
	
	private:
		
		inline void PrivateAddRef() const noexcept
		{
			if (this->ptr != nullptr)
			{
				this->ptr->AddRef();
			}
		}
		
		inline size_t PrivateRelease() noexcept
		{
			size_t ref = 0;
			T *temp = this->ptr;
			
			if (temp != nullptr)
			{
				this->ptr = nullptr;
				ref = temp->Release();
			}
			
			return ref;
		}
	
	public:
		
		///
		/// 获取指针
		///
		///
		inline T *Get() const noexcept { return this->ptr; };
		
		///
		/// 获取指针
		///
		///
		inline T *const *GetAddressOf() const noexcept { return &this->ptr; }
		
		///
		/// 获取指针
		///
		///
		inline T **GetAddressOf() noexcept { return &this->ptr; }
	
	private:
		
		T *ptr;
		
	};
	
	
	template<class T>
	inline TPtr<T>::TPtr() noexcept
		: ptr(nullptr)
	{
	
	}
	
	template<class T>
	inline TPtr<T>::TPtr(nullptr_t _other) noexcept
		: ptr(nullptr)
	{
	
	}
	
	template<class T>
	inline TPtr<T>::TPtr(const TPtr &_other) noexcept
		: ptr(_other.ptr)
	{
		PrivateAddRef();
	}
	
	template<class T>
	inline TPtr<T>::TPtr(T *_ptr) noexcept
		: ptr(_ptr)
	{
		PrivateAddRef();
	}
	
	template<class T>
	inline TPtr<T>::~TPtr() noexcept
	{
		PrivateRelease();
	}
	
	template<class T>
	inline TPtr<T> &TPtr<T>::operator=(const TPtr &_other) noexcept
	{
		PrivateRelease();
		this->ptr = _other.ptr;
		PrivateAddRef();
		return *this;
	}
	
	template<class T>
	inline bool TPtr<T>::operator==(const TPtr &_other) const noexcept
	{
		if (this->ptr == _other.ptr) return true;
		if (this->ptr == nullptr || _other.ptr == nullptr) return false;
		return this->ptr->operator==(*_other.ptr);
	}
	
	template<class T>
	inline bool TPtr<T>::operator!=(const TPtr &_other) const noexcept
	{
		if (this->ptr == _other.ptr) return false;
		if (this->ptr == nullptr || _other.ptr == nullptr) return true;
		return this->ptr->operator!=(*_other.ptr);
	}
	
	template<class T>
	inline size_t TPtr<T>::Reset() noexcept
	{
		return PrivateRelease();
	}
	
	template<class T>
	inline const type_info &TPtr<T>::TypeId() const noexcept
	{
		return typeid(*this->ptr);
	}
	
	template<class T>
	template<class U>
	inline U *TPtr<T>::Cast() const noexcept
	{
		return dynamic_cast<U *>(this->ptr);
	}
	
}


