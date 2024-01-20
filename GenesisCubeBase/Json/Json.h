#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"
#include "../Object/GBool.h"
#include "../Object/GFloat.h"
#include "../Object/GInteger.h"
#include "../Object/GNull.h"
#include "../Object/GString.h"
#include "../Exception/Exception.h"
#include "../Core/TPtr.h"

namespace GenesisCube::JSON
{
	
	/// 
	/// json对象
	/// 
	class Json
	{
	public:
		
		typedef std::vector<Json> Array;
		
		typedef std::map<TString, Json> Object;
		
		typedef Array::iterator ArrayIterator;
		
		typedef Object::iterator ObjectIterator;
		
		typedef Array::reverse_iterator ArrayReverseIterator;
		
		typedef Object::reverse_iterator ObjectReverseIterator;
	
	public:
		
		Json();
		
		Json(bool _bool);
		
		Json(int32_t integer);
		
		Json(uint32_t integer);
		
		Json(int64_t integer);
		
		Json(double_t _float);
		
		Json(const TString &_string);
		
		Json(const TChar *_string);
		
		Json(const NTChar *_string) = delete;
		
		Json(nullptr_t _null);
		
		Json(const Json &_other);
		
		~Json();
	
	public:
		
		Json &operator=(const Json &_other);
		
		Json &operator[](size_t index) const;
		
		Json &operator[](size_t index);
		
		Json &operator[](int32_t index) const;
		
		Json &operator[](int32_t index);
		
		Json &operator[](const TChar *key) const;
		
		Json &operator[](const TChar *key);
		
		Json &operator[](const NTChar *key) const = delete;
		
		Json &operator[](const NTChar *key) = delete;
		
		Json &operator[](const TString &key) const;
		
		Json &operator[](const TString &key);
		
		bool operator==(const Json &_other);
		
		bool operator!=(const Json &_other);
	
	public:
		
		///
		/// 错误JSON，当调用该类的函数出现错误时返回
		static Json errorJson;
		
		/// 
		/// 数组：添加元素
		///
		void Push(const Json &_json);
		
		/// 
		/// 数组：减少元素
		///
		void Pop();
		
		/// 
		/// 数组：有一个。不是数组返回false
		///
		[[nodiscard]] bool Has(size_t index) const;
		
		/// 
		/// 对象：有一个。不是对象返回false
		///
		[[nodiscard]] bool Has(const TString &key) const;
		
		/// 
		/// 数组：删除元素
		/// 
		/// \param index 索引
		/// \return 
		ArrayIterator Remove(size_t index);
		
		/// 
		/// 数组：删除元素
		/// 
		/// \param _First 开始位置
		/// \param _Last 结束位置
		/// \return 
		ArrayIterator Remove(const ArrayIterator &_First, const ArrayIterator &_Last);
		
		/// 
		/// 数组：删除元素
		/// 
		/// \param _Where 位置
		/// \return 
		ArrayIterator Remove(const ArrayIterator &_Where);
		
		/// 
		/// 对象：删除元素
		/// 
		/// \param key 键
		/// \return 删除元素数量
		size_t Remove(const TString &key);
		
		/// 
		/// 对象：删除元素
		/// 
		/// \param _First 开始位置
		/// \param _Last 结束位置
		/// \return 
		ObjectIterator Remove(const ObjectIterator &_First, const ObjectIterator &_Last);
		
		/// 
		/// 对象：删除元素
		/// 
		/// \param _Where 位置
		/// \return 
		ObjectIterator Remove(const ObjectIterator &_Where);
		
		/// 
		/// 数组：元素个数。
		/// 对象：键值对个数
		/// 
		/// \return 个数
		[[nodiscard]] size_t Size() const;
		
		/// 
		/// 开始iterator，用于foreach，无法遍历数组
		/// 
		/// \return 
		[[nodiscard]] ObjectIterator begin() const;
		
		/// 
		/// 结束iterator，用于foreach，无法遍历数组
		/// 
		/// \return 
		[[nodiscard]] ObjectIterator end() const;
		
		/// 
		/// 开始iterator
		/// 
		/// \return 
		[[nodiscard]] ArrayIterator ArrayBegin() const;
		
		/// 
		/// 结束iterator
		/// 
		/// \return 
		[[nodiscard]] ArrayIterator ArrayEnd() const;
		
		/// 
		/// 反转开始iterator
		/// 
		/// \return 
		[[nodiscard]] ArrayReverseIterator ArrayRBegin() const;
		
		/// 
		/// 反转结束iterator
		/// 
		/// \return 
		[[nodiscard]] ArrayReverseIterator ArrayREnd() const;
		
		/// 
		/// 开始iterator
		/// 
		/// \return 
		[[nodiscard]] ObjectIterator ObjectBegin() const;
		
		/// 
		/// 结束iterator
		/// 
		/// \return 
		[[nodiscard]] ObjectIterator ObjectEnd() const;
		
		/// 
		/// 反转开始iterator
		/// 
		/// \return 
		[[nodiscard]] ObjectReverseIterator ObjectRBegin() const;
		
		/// 
		/// 反转结束iterator
		/// 
		/// \return 
		[[nodiscard]] ObjectReverseIterator ObjectREnd() const;
		
		/// 
		/// 数组：转换为vector数组
		/// 
		/// \return 
		[[nodiscard]] Array &ToArray() const;
		
		/// 
		/// 对象：转换为map
		/// 
		/// \return 
		[[nodiscard]] Object &ToMap() const;
		
		/// 
		/// 重置为GNull
		/// 
		void Reset();
		
		/// 
		/// 判断类型
		/// 
		/// \return bool
		template<class T>
		[[nodiscard]] inline bool Is() const { return GenesisCube::Is<T>(this->json); }
		
		///
		/// \return
		[[nodiscard]]
		inline GString::ValueType GetString(const GString::ValueType &defaultValue) const
		{
			return Get<GString>(defaultValue);
		}
		
		///
		/// \return
		[[nodiscard]]
		inline GInteger::ValueType GetInteger(const GInteger::ValueType &defaultValue = 0) const
		{
			return Get<GInteger>(defaultValue);
		}
		
		///
		/// \return
		[[nodiscard]]
		inline float_t GetFloat(const float_t &defaultValue = 0.0f) const
		{
			return (float_t) Get<GFloat>((double_t) defaultValue);
		}
		
		///
		/// \return
		[[nodiscard]]
		inline GFloat::ValueType GetDouble(const GFloat::ValueType &defaultValue = 0.0) const
		{
			return Get<GFloat>(defaultValue);
		}
		
		///
		/// \return
		[[nodiscard]]
		inline GBool::ValueType GetBool(const GBool::ValueType &defaultValue) const
		{
			return Get<GBool>(defaultValue);
		}
		
		/// 
		/// 转换类型并获取
		/// 
		/// \return
		template<class T, class U = T::ValueType>
		inline U Get(const U &defaultValue) const;
	
	public:
		
		[[nodiscard]]
		TString ToString() const noexcept;
	
	private:
		
		TSharedPtr<GObject> json;
		
	};
	
	template<class T, class U>
	inline U Json::Get(const U &defaultValue) const
	{
		const TSharedPtr<T> ptr = PtrCast<T>(this->json);
		if (ptr == nullptr) return defaultValue;
		return ptr->Get();
	}
	
}
