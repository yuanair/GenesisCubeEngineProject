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

namespace GenesisCubeEngine::JSON
{
	
	/// <summary>
	/// json对象
	/// </summary>
	class Json : public GObject
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
		
		Json(int32_t _interger);
		
		Json(uint32_t _interger);
		
		Json(int64_t _interger);
		
		Json(double_t _float);
		
		Json(const TString &_string);
		
		Json(const TChar *_string);
		
		Json(const NTChar *_string) = delete;
		
		Json(nullptr_t _null);
		
		Json(const Json &_other);
		
		~Json() override;
	
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
		
		operator bool() const;
		
		operator int64_t() const;
		
		operator double_t() const;
		
		operator TString() const;
		
		operator nullptr_t() const;
		
		operator int8_t() const = delete;
		
		operator uint8_t() const = delete;
		
		operator int16_t() const = delete;
		
		operator uint16_t() const = delete;
		
		operator int32_t() const = delete;
		
		operator uint32_t() const = delete;
		
		operator uint64_t() const = delete;
		
		operator TChar() const = delete;
		
		operator NTChar() const = delete;
	
	public:
		
		/// <summary>
		/// 数组：添加元素
		/// </summary>
		/// <returns></returns>
		void Push(const Json &_json);
		
		/// <summary>
		/// 数组：减少元素
		/// </summary>
		/// <returns></returns>
		void Pop();
		
		/// <summary>
		/// 数组：有一个。不是数组返回false
		/// </summary>
		/// <param name="key"></param>
		[[nodiscard]] bool Has(size_t index) const;
		
		/// <summary>
		/// 对象：有一个。不是对象返回false
		/// </summary>
		/// <param name="key"></param>
		[[nodiscard]] bool Has(const TString &key) const;
		
		/// <summary>
		/// 数组：删除元素
		/// </summary>
		/// <param name="index">索引</param>
		/// <returns></returns>
		ArrayIterator Remove(size_t index);
		
		/// <summary>
		/// 数组：删除元素
		/// </summary>
		/// <param name="_First">开始位置</param>
		/// <param name="_Last">结束位置</param>
		/// <returns></returns>
		ArrayIterator Remove(const ArrayIterator &_First, const ArrayIterator &_Last);
		
		/// <summary>
		/// 数组：删除元素
		/// </summary>
		/// <param name="_Where">位置</param>
		/// <returns></returns>
		ArrayIterator Remove(const ArrayIterator &_Where);
		
		/// <summary>
		/// 对象：删除元素
		/// </summary>
		/// <param name="key">键</param>
		/// <returns>删除元素数量</returns>
		size_t Remove(const TString &key);
		
		/// <summary>
		/// 对象：删除元素
		/// </summary>
		/// <param name="_First">开始位置</param>
		/// <param name="_Last">结束位置</param>
		/// <returns></returns>
		ObjectIterator Remove(const ObjectIterator &_First, const ObjectIterator &_Last);
		
		/// <summary>
		/// 对象：删除元素
		/// </summary>
		/// <param name="_Where">位置</param>
		/// <returns></returns>
		ObjectIterator Remove(const ObjectIterator &_Where);
		
		/// <summary>
		/// 数组：元素个数。
		/// 对象：键值对个数
		/// </summary>
		/// <returns>个数</returns>
		[[nodiscard]] size_t Size() const;
		
		/// <summary>
		/// 开始iterator，用于foreach，无法遍历数组
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ObjectIterator begin() const;
		
		/// <summary>
		/// 结束iterator，用于foreach，无法遍历数组
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ObjectIterator end() const;
		
		/// <summary>
		/// 开始iterator
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ArrayIterator ArrayBegin() const;
		
		/// <summary>
		/// 结束iterator
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ArrayIterator ArrayEnd() const;
		
		/// <summary>
		/// 反转开始iterator
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ArrayReverseIterator ArrayRBegin() const;
		
		/// <summary>
		/// 反转结束iterator
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ArrayReverseIterator ArrayREnd() const;
		
		/// <summary>
		/// 开始iterator
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ObjectIterator ObjectBegin() const;
		
		/// <summary>
		/// 结束iterator
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ObjectIterator ObjectEnd() const;
		
		/// <summary>
		/// 反转开始iterator
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ObjectReverseIterator ObjectRBegin() const;
		
		/// <summary>
		/// 反转结束iterator
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] ObjectReverseIterator ObjectREnd() const;
		
		/// <summary>
		/// 数组：转换为vector数组
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] Array &ToArray() const;
		
		/// <summary>
		/// 对象：转换为map
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] Object &ToMap() const;
		
		/// <summary>
		/// 重置为GNull
		/// </summary>
		void Reset();
		
		/// <summary>
		/// 获取类型
		/// </summary>
		/// <returns>类型</returns>
		[[nodiscard]] inline const type_info &TypeId() const { return this->json.TypeId(); }
		
		/// <summary>
		/// 判断类型
		/// </summary>
		/// <returns>bool</returns>
		template<class T>
		[[nodiscard]] inline bool Is() const { return TypeId() == typeid(T); }
		
		/// <summary>
		/// 转换类型并获取
		/// </summary>
		/// <returns>auto</returns>
		template<class T>
		inline auto Get() const;
		
		/// <summary>
		/// 克隆
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] Json *Clone() const noexcept override
		{
			Json *ptr = new Json();
			ptr->json = this->json;
			return ptr;
		}
	
	private:
		
		TPtr<GObject> json;
		
	};
	
	template<class T>
	inline auto Json::Get() const
	{
		const T *ptr = this->json.Cast<T>();
		if (ptr == nullptr) throw ENullptrException(__FUNCSIG__ TEXT(":: cannot cast to be a T"));
		return ptr->Get();
	}
	
}
