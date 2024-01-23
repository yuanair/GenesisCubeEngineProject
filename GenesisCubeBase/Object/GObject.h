//
// Created by admin on 2023/12/19.
//

#pragma once

#include "../Core/FCore.h"


namespace GenesisCube
{
	
	//
	// 对象
	//
	class GObject
	{
	public:
		
		GObject() = default;
		
		GObject(const GObject &object) = delete;
		
		virtual ~GObject() = default;
	
	public:
		
		GObject &operator=(const GObject &) = delete;
	
	public:
		
		///
		/// 克隆
		///
		/// \return 克隆体
		[[nodiscard]]
		virtual GObject *Clone() const noexcept = 0;
		
		///
		/// 转换为字符串
		/// \return 字符串
		[[nodiscard]]
		virtual TString ToString() const noexcept;
		
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
