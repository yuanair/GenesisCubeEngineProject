//
// Created by admin on 2023/12/24.
//

#pragma once

#include "../Core/Header.h"
#include "../../GenesisCubeBase/Object/GObject.h"
#include "../Debug/Debug.h"
#include "FResult.h"

namespace GenesisCube
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
		
		TUnknown(const Ptr &ptr) : ptr(ptr) {}
		
		template<class U>
		TUnknown(const TUnknown<U> &other) : ptr(other.GetComPtr()) {}
		
		~TUnknown() noexcept override = default;
	
	public:
		
		virtual Microsoft::WRL::ComPtr<T> &GetComPtr() { return this->ptr; }
		
		virtual const Microsoft::WRL::ComPtr<T> &GetComPtr() const { return this->ptr; }
	
	public:
		
		///
		inline void Reset() noexcept { GetComPtr().Reset(); }
		
		///
		inline operator bool() const noexcept { return GetComPtr().operator Microsoft::WRL::Details::BoolType(); }
		
		///
		/// \return 指针
		inline T *Get() const noexcept { return GetComPtr().Get(); }
		
		///
		/// \return 指向指针的指针
		inline T *const *GetAddressOf() const noexcept { return GetComPtr().GetAddressOf(); }
		
		///
		/// \return 指向指针的指针
		inline T **GetAddressOf() noexcept { return GetComPtr().GetAddressOf(); }
		
		///
		/// \return 指向指针的指针
		inline T **ReleaseAndGetAddressOf() noexcept { return GetComPtr().ReleaseAndGetAddressOf(); }
		
		///
		/// \return 引用
		inline PtrRef operator&() noexcept { return &GetComPtr(); }
		
		///
		/// \return 引用
		inline ConstPtrRef operator&() const noexcept { return &GetComPtr(); }
		
		///
		/// \return HRESULT
		template<typename U>
		inline HRESULT As(Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<U>> p) const noexcept
		{
			return GetComPtr().As(p);
		}
		
		///
		/// \tparam U
		/// \param p
		/// \return HRESULT
		template<typename U>
		inline HRESULT As(Microsoft::WRL::ComPtr<U> *p) const noexcept
		{
			return GetComPtr().As(p);
		}
		
		///
		/// 如果为nullptr则抛出异常
		///
		void ThrowIfNull() const noexcept(false)
		{
			if (!GetComPtr()) throw ENullptrException(__FUNCSIG__ TEXT(":: nullptr exception"));
		}
	
	public:
		
		TUnknown *Clone() const noexcept override { return new TUnknown(this->ptr); }
	
	private:
		
		Ptr ptr;
		
	};
	
} // GenesisCube
