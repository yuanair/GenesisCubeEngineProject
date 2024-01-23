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

namespace GenesisCube::Json
{
	
	template<class T>
	struct JsonObject
	{
	
	};
	
	template<>
	struct JsonObject<std::nullptr_t>
	{
		typedef std::nullptr_t JsonType;
	};
	
	template<>
	struct JsonObject<int64_t>
	{
		typedef GInteger JsonType;
	};
	
	template<>
	struct JsonObject<double_t>
	{
		typedef GFloat JsonType;
	};
	
	template<>
	struct JsonObject<bool>
	{
		typedef GBool JsonType;
	};
	
	template<>
	struct JsonObject<TString>
	{
		typedef GString JsonType;
	};
	
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
		ArrayIterator Remove(const ArrayIterator &First, const ArrayIterator &Last);
		
		/// 
		/// 数组：删除元素
		/// 
		/// \param _Where 位置
		/// \return 
		ArrayIterator Remove(const ArrayIterator &Where);
		
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
		ObjectIterator Remove(const ObjectIterator &First, const ObjectIterator &Last);
		
		/// 
		/// 对象：删除元素
		/// 
		/// \param _Where 位置
		/// \return 
		ObjectIterator Remove(const ObjectIterator &Where);
		
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
		[[nodiscard]]
		inline bool Is() const { return GenesisCube::Is<T>(this->json.get()); }
		
		///
		/// \return
		[[nodiscard]]
		inline TString GetString(const TString &defaultValue) const
		{
			return Get<TString>(defaultValue);
		}
		
		///
		/// \return
		[[nodiscard]]
		inline int64_t GetInteger(const int64_t &defaultValue = 0) const
		{
			return Get<int64_t>(defaultValue);
		}
		
		///
		/// \return
		[[nodiscard]]
		inline float_t GetFloat(const float_t &defaultValue = 0.0f) const
		{
			return (float_t) Get<double_t>((double_t) defaultValue);
		}
		
		///
		/// \return
		[[nodiscard]]
		inline double_t GetDouble(const double_t &defaultValue = 0.0) const
		{
			return Get<double_t>(defaultValue);
		}
		
		///
		/// \return
		[[nodiscard]]
		inline bool GetBool(const bool &defaultValue) const
		{
			return Get<bool>(defaultValue);
		}
		
		/// 
		/// 转换类型并获取
		/// 
		/// \return
		template<class T, class U = JsonObject<T>::JsonType>
		inline T Get(const T &defaultValue) const;
	
	
	public:
		
		[[nodiscard]]
		TString ToString() const noexcept;
	
	private:
		
		TUniquePtr<GObject> json;
		
	};
	
	template<class T, class U>
	inline T Json::Get(const T &defaultValue) const
	{
		U *ptr = PtrCast<U>(this->json);
		if (ptr == nullptr) return defaultValue;
		return ptr->Get();
	}
	
}
