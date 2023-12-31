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
		/// 获取类型
		/// 
		/// \return 类型
		[[nodiscard]] inline const type_info &TypeId() const { return this->json.TypeId(); }
		
		/// 
		/// 判断类型
		/// 
		/// \return bool
		template<class T>
		[[nodiscard]] inline bool Is() const { return TypeId() == typeid(T); }
		
		/// 
		/// 转换类型并获取
		/// 
		/// \return auto
		template<class T>
		inline auto Get() const;
		
		[[nodiscard]] Json *Clone() const noexcept override
		{
			Json *ptr = new Json();
			ptr->json = this->json;
			return ptr;
		}
		
		GCLASS_BODY(Json)
		
		[[nodiscard]] TString ToString() const noexcept override;
	
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
