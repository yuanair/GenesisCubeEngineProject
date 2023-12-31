//
// Created by admin on 2023/12/19.
//

#pragma once

#include "../Core/FCore.h"

#define GCLASS_BODY(className) \
inline TString GetName() const noexcept override { return TEXT(# className); } \
inline static TString GetStaticName() noexcept { return TEXT(# className); }

namespace GenesisCube
{
	//
	// 对象
	//
	class GObject
	{
		
		template<class T> friend
		class TPtr;
	
	public:
		
		GObject() noexcept;
		
		virtual ~GObject() noexcept(false);
		
		GObject(const GObject &) = delete;
		
		GObject &operator=(const GObject &) = delete;
	
	public:
		
		///
		/// 相等运算符
		///
		/// \param _other 比较对象
		/// \return 结果
		inline virtual bool operator==(const GObject &_other) const { return this == &_other; }
		
		///
		/// 不相等运算符
		///
		/// \param _other 比较对象
		/// \return 结果
		inline virtual bool operator!=(const GObject &_other) const { return this != &_other; }
		
		///
		/// 克隆
		///
		/// \return 克隆体
		[[nodiscard]]
		inline virtual GObject *Clone() const noexcept = 0;
		
		///
		/// 转换为字符串
		/// \return 字符串
		[[nodiscard]]
		inline virtual TString ToString() const noexcept;
		
		///
		/// 获取类名
		/// \return 类名
		[[nodiscard]]
		inline virtual TString GetName() const noexcept = 0;
	
	private:
		
		///
		/// 添加引用，无需手动调用
		///
		/// \return 引用计数
		size_t AddRef() noexcept;
		
		///
		/// 释放，无需手动调用
		///
		/// \return 引用计数
		size_t Release() noexcept;
	
	public:
		
		///
		/// 获取引用计数
		///
		/// \return 引用计数
		[[nodiscard]]
		inline size_t GetRef() const noexcept { return this->ref; }
	
	private:
		
		size_t ref;
		
	};
	
	///
	/// \tparam T
	/// \param value
	/// \return
	template<class T>
	inline TString ToTString(T value)
	{
#if defined(UNICODE)
		return std::to_wstring(value);
#else
		return std::to_string(value);
#endif
	}
	
} // GenesisCube
