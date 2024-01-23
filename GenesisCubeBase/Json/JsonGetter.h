//
// Created by admin on 2024/1/23.
//

#pragma once

#include <utility>

#include "Json.h"

namespace GenesisCube::Json
{
	
	class IJsonGetter
	{
	public:
		
		inline virtual Json &GetJson() = 0;
		
	};
	
	
	///
	/// Json值获取器
	///
	class FJsonGetter : public IJsonGetter
	{
	public:
		
		inline FJsonGetter(Json &json)
			: json(json)
		{
		
		}
	
	public:
		
		inline Json &GetJson() override { return this->json; }
	
	protected:
		
		Json &json;
		
	};
	
	
	///
	/// Json值获取器
	///
	class FJsonGetterGetter : public IJsonGetter
	{
	public:
		
		inline explicit FJsonGetterGetter(IJsonGetter &jsonGetter)
			: jsonGetter(jsonGetter)
		{
		
		}
	
	public:
		
		inline Json &GetJson() override { return this->jsonGetter.GetJson(); }
	
	protected:
		
		IJsonGetter &jsonGetter;
		
	};
	
	///
	/// JObject值获取器
	///
	class FJObjectGetter : public FJsonGetterGetter
	{
	public:
		
		inline FJObjectGetter(IJsonGetter &jsonGetter, TString key)
			: FJsonGetterGetter(jsonGetter), key(std::move(key))
		{
		
		}
		
		inline ~FJObjectGetter() = default;
	
	public:
		
		///
		/// \param json Json
		/// \return 值
		[[nodiscard]]
		inline Json &GetJson() override
		{
			return FJsonGetterGetter::GetJson()[key];
		}
	
	public:
		
		const TString key;
		
	};
	
	///
	/// JArray值获取器
	///
	class FJArrayGetter : public FJsonGetterGetter
	{
	public:
		
		inline FJArrayGetter(IJsonGetter &jsonGetter, size_t index)
			: FJsonGetterGetter(jsonGetter), index(index)
		{
		
		}
		
		inline ~FJArrayGetter() = default;
	
	public:
		
		///
		/// \return 值
		[[nodiscard]]
		inline Json &GetJson() override
		{
			return FJsonGetterGetter::GetJson()[index];
		}
	
	public:
		
		const size_t index;
		
	};
	
	///
	/// Json值获取器
	///
	template<class T>
	class TJsonValueGetter : public FJsonGetterGetter
	{
	public:
		
		inline explicit TJsonValueGetter(IJsonGetter &jsonGetter, T defaultValue)
			: FJsonGetterGetter(jsonGetter), defaultValue(std::move(defaultValue))
		{
		
		}
		
		inline ~TJsonValueGetter() = default;
	
	public:
		
		///
		/// \param json Json
		/// \return 值
		inline virtual T Get()
		{
			return GetJson().template Get<T>(this->defaultValue);
		}
	
	public:
		
		const T defaultValue;
		
	};
	
	///
	/// JObject值获取器
	/// \tparam T 类型
	template<class T>
	class TJObjectValueGetter : private FJObjectGetter, public TJsonValueGetter<T>
	{
	public:
		
		inline explicit TJObjectValueGetter(IJsonGetter &jsonGetter, const TString &key)
			: FJObjectGetter(jsonGetter, key),
			  TJsonValueGetter<T>((FJObjectGetter &) *this, key)
		{
		
		}
		
		inline explicit TJObjectValueGetter(IJsonGetter &jsonGetter, TString key, const T &defaultValue)
			: FJObjectGetter(jsonGetter, std::move(key)),
			  TJsonValueGetter<T>((FJObjectGetter &) *this, defaultValue)
		{
		
		}
	
	public:
		
		///
		/// \param json Json
		/// \return 值
		inline T Get() override
		{
			return TJsonValueGetter<T>::Get();
		}
		
		
	};
	
	///
	/// JArray值获取器
	/// \tparam T 类型
	template<class T>
	class TJArrayValueGetter : private FJArrayGetter, public TJsonValueGetter<T>
	{
	public:
		
		inline explicit TJArrayValueGetter(IJsonGetter &jsonGetter, size_t index, const T &defaultValue)
			: FJArrayGetter(jsonGetter, index), TJsonValueGetter<T>((FJArrayGetter &) *this, defaultValue)
		{
		
		}
	
	public:
		
		///
		/// \param json Json
		/// \return 值
		inline T Get() override
		{
			return TJsonValueGetter<T>::Get();
		}
		
		
	};
	
} // GenesisCube
