#include "Json.h"

#include "JArray.h"
#include "JObject.h"

namespace GenesisCube::Json
{
	
	Json Json::Json::errorJson{};
	
	Json::Json::Json()
		: json(new GNull)
	{
	
	}
	
	Json::Json::Json(bool _bool)
		: json(new GBool(_bool))
	{
	
	}
	
	Json::Json::Json(int32_t integer)
		: json(new GInteger(integer))
	{
	
	}
	
	Json::Json::Json(uint32_t integer)
		: json(new GInteger(integer))
	{
	
	}
	
	Json::Json::Json(int64_t integer)
		: json(new GInteger(integer))
	{
	
	}
	
	Json::Json::Json(double_t _float)
		: json(new GFloat(_float))
	{
	
	}
	
	Json::Json::Json(const TString &_string)
		: json(new GString(_string))
	{
	
	}
	
	Json::Json::Json(const TChar *_string)
		: json(new GString(_string))
	{
	
	}
	
	Json::Json::Json(nullptr_t)
		: json(new GNull)
	{
	
	}
	
	Json::Json::Json(const Json &_other)
		: json(_other.json->Clone())
	{
	
	}
	
	Json::Json::~Json()
	= default;
	
	Json &Json::Json::operator=(const Json &_other)
	{
		this->json = TUniquePtr<GObject>(_other.json->Clone());
		return *this;
	}
	
	Json &Json::Json::operator[](size_t index) const
	{
		if (auto *arr = PtrCast<JArray>(this->json))
		{
			for (size_t i = arr->values.size(); i <= index; i++)
			{
				Json buffer;
				arr->values.push_back(buffer);
			}
			return arr->values[index];
		}
		return errorJson = __FUNCSIG__ TEXT(":: This is not an array");
	}
	
	Json &Json::Json::operator[](size_t index)
	{
		if (auto *arr = PtrCast<JArray>(this->json))
		{
			for (size_t i = arr->values.size(); i <= index; i++)
			{
				Json buffer;
				arr->values.push_back(buffer);
			}
			return arr->values[index];
		}
		if (!Is<GNull>()) return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
		auto *arr = new JArray;
		
		for (size_t i = arr->values.size(); i <= index; i++)
		{
			Json buffer;
			arr->values.push_back(buffer);
		}
		this->json = TUniquePtr<JArray>(arr);
		return arr->values[index];
	}
	
	Json &Json::Json::operator[](int32_t index) const
	{
		return this->operator[]((size_t) index);
	}
	
	Json &Json::Json::operator[](int32_t index)
	{
		return this->operator[]((size_t) index);
	}
	
	Json &Json::Json::operator[](const TCHAR *key) const
	{
		if (auto *arr = PtrCast<JObject>(this->json.get()))
		{
			return arr->values[key];
		}
		return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	Json &Json::Json::operator[](const TCHAR *key)
	{
		if (auto *arr = PtrCast<JObject>(this->json))
		{
			return arr->values[key];
		}
		if (!Is<GNull>()) return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
		auto *arr = new JObject;
		this->json = TUniquePtr<JObject>(arr);
		return arr->values[key];
	}
	
	Json &Json::Json::operator[](const TString &key) const
	{
		if (auto *arr = PtrCast<JObject>(this->json))
		{
			return arr->values[key];
		}
		return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	Json &Json::Json::operator[](const TString &key)
	{
		if (auto *arr = PtrCast<JObject>(this->json))
		{
			return arr->values[key];
		}
		if (!Is<GNull>()) return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
		auto *arr = new JObject;
		this->json = TUniquePtr<JObject>(arr);
		
		Json buffer;
		return arr->values[key] = buffer;
	}
	
	bool Json::Json::operator==(const Json &_other)
	{
		return this->json == _other.json;
	}
	
	bool Json::Json::operator!=(const Json &_other)
	{
		return this->json != _other.json;
	}
	
	void Json::Json::Push(const Json &_json)
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			arr->values.push_back(_json);
			return;
		}
		if (!Is<GNull>()) throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
		auto *arr = new JArray;
		arr->values.push_back(_json);
		this->json = TUniquePtr<JArray>(arr);
	}
	
	void Json::Json::Pop()
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			arr->values.pop_back();
			return;
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	bool Json::Json::Has(size_t index) const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return index < arr->values.size();
		}
		return false;
	}
	
	bool Json::Json::Has(const TString &key) const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.find(key) != obj->values.end();
		}
		return false;
	}
	
	Json::Json::ArrayIterator Json::Json::Remove(size_t index)
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			if (index >= arr->values.size()) throw EOutOfRangeException(__FUNCSIG__ TEXT(":: out of range"));
			return arr->values.erase(arr->values.begin() + index);
		}
		return {};
	}
	
	Json::Json::ArrayIterator Json::Json::Remove(const ArrayIterator &First, const ArrayIterator &Last)
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.erase(First, Last);
		}
		return {};
	}
	
	Json::Json::ArrayIterator Json::Json::Remove(const ArrayIterator &Where)
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.erase(Where);
		}
		return {};
	}
	
	size_t Json::Json::Remove(const TString &key)
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.erase(key);
		}
		return 0;
	}
	
	Json::Json::ObjectIterator Json::Json::Remove(const ObjectIterator &First, const ObjectIterator &Last)
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.erase(First, Last);
		}
		return {};
	}
	
	Json::Json::ObjectIterator Json::Json::Remove(const ObjectIterator &Where)
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.erase(Where);
		}
		return {};
	}
	
	Json::Json::ObjectIterator Json::Json::begin() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.begin();
		}
		return {};
	}
	
	Json::Json::ObjectIterator Json::Json::end() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.end();
		}
		return {};
	}
	
	size_t Json::Json::Size() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.size();
		}
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.size();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array or an object"));
	}
	
	Json::Json::ArrayIterator Json::Json::ArrayBegin() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.begin();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	Json::Json::ArrayIterator Json::Json::ArrayEnd() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.end();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	Json::Json::ArrayReverseIterator Json::Json::ArrayRBegin() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.rbegin();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	Json::Json::ArrayReverseIterator Json::Json::ArrayREnd() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.rend();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	Json::Json::ObjectIterator Json::Json::ObjectBegin() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.begin();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	Json::Json::ObjectIterator Json::Json::ObjectEnd() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.end();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	Json::Json::ObjectReverseIterator Json::Json::ObjectRBegin() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.rbegin();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	Json::Json::ObjectReverseIterator Json::Json::ObjectREnd() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.rend();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	Json::Json::Array &Json::Json::ToArray() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values;
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	Json::Json::Object &Json::Json::ToMap() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values;
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	void Json::Json::Reset()
	{
		this->json = MakeUnique<GNull>();
	}
	
	TString Json::Json::ToString() const noexcept
	{
		return this->json->ToString();
	}
	
}