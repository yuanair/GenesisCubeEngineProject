//
// Created by admin on 2023/12/24.
//

#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"
#include "../Debug/Debug.h"

namespace GenesisCubeEngine
{
	
	///
	/// DirectX基类
	///
	template<class T>
	class TUnknown : public GObject
	{
	public:
		
		typedef T Type;
		
		typedef Microsoft::WRL::ComPtr<T> Ptr;
		
		typedef Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<T>> PtrRef;
		
		typedef const Microsoft::WRL::Details::ComPtrRef<const Microsoft::WRL::ComPtr<T>> ConstPtrRef;
	
	public:
		
		TUnknown() noexcept = default;
		
		explicit TUnknown(const Ptr &ptr) : ptr(ptr) {}
		
		~TUnknown() noexcept override = default;
	
	public:
		
		///
		inline void Reset() noexcept { this->ptr.Reset(); }
		
		///
		inline operator bool() const noexcept { return this->ptr.operator Microsoft::WRL::Details::BoolType(); }
		
		///
		/// \return 指针
		inline T *Get() const noexcept { return ptr.Get(); }
		
		///
		/// \return 指向指针的指针
		inline T *const *GetAddressOf() const noexcept { return ptr.GetAddressOf(); }
		
		///
		/// \return 指向指针的指针
		inline T **GetAddressOf() noexcept { return ptr.GetAddressOf(); }
		
		///
		/// \return 指向指针的指针
		inline T **ReleaseAndGetAddressOf() noexcept { return ptr.ReleaseAndGetAddressOf(); }
		
		///
		/// \return 引用
		inline PtrRef operator&() noexcept { return &ptr; }
		
		///
		/// \return 引用
		inline ConstPtrRef operator&() const noexcept { return &ptr; }
		
		///
		/// \return HRESULT
		template<typename U>
		inline HRESULT As(Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<U>> p) const noexcept
		{
			return this->ptr.As(p);
		}
		
		///
		/// \tparam U
		/// \param p
		/// \return HRESULT
		template<typename U>
		inline HRESULT As(Microsoft::WRL::ComPtr<U> *p) const noexcept
		{
			return this->ptr.As(p);
		}
	
	public:
		
		TUnknown *Clone() const noexcept override { return new TUnknown(this->ptr); }
	
	protected:
		
		Ptr ptr;
		
	};
	
} // GenesisCubeEngine
