#include "Json.h"

#include "JArray.h"
#include "JObject.h"

namespace GenesisCube
{
	
	JSON::Json JSON::Json::errorJson{};
	
	JSON::Json::Json()
	{
		this->json = MakeShared<GNull>();
	}
	
	JSON::Json::Json(bool _bool)
	{
		this->json = MakeShared<GBool>(_bool);
	}
	
	JSON::Json::Json(int32_t integer)
	{
		this->json = MakeShared<GInteger>(integer);
	}
	
	JSON::Json::Json(uint32_t integer)
	{
		this->json = MakeShared<GInteger>(integer);
	}
	
	JSON::Json::Json(int64_t integer)
	{
		this->json = MakeShared<GInteger>(integer);
	}
	
	JSON::Json::Json(double_t _float)
	{
		this->json = MakeShared<GFloat>(_float);
	}
	
	JSON::Json::Json(const TString &_string)
	{
		this->json = MakeShared<GString>(_string);
	}
	
	JSON::Json::Json(const TChar *_string)
	{
		this->json = MakeShared<GString>(_string);
	}
	
	JSON::Json::Json(nullptr_t)
	{
		this->json = MakeShared<GNull>();
	}
	
	JSON::Json::Json(const Json &_other)
	{
		this->json = _other.json;
	}
	
	JSON::Json::~Json()
	= default;
	
	JSON::Json &JSON::Json::operator=(const JSON::Json &_other)
	{
		this->json = _other.json;
		return *this;
	}
	
	JSON::Json &JSON::Json::operator[](size_t index) const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			for (size_t i = arr->values.size(); i <= index; i++)
			{
				JSON::Json buffer;
				arr->values.push_back(buffer);
			}
			return arr->values[index];
		}
		return errorJson = __FUNCSIG__ TEXT(":: This is not an array");
	}
	
	JSON::Json &JSON::Json::operator[](size_t index)
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			for (size_t i = arr->values.size(); i <= index; i++)
			{
				JSON::Json buffer;
				arr->values.push_back(buffer);
			}
			return arr->values[index];
		}
		if (!Is<GNull>()) return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
		auto arr = MakeShared<JArray>();
		
		for (size_t i = arr->values.size(); i <= index; i++)
		{
			JSON::Json buffer;
			arr->values.push_back(buffer);
		}
		this->json = arr;
		return PtrCast<JArray>(this->json)->values[index];
	}
	
	JSON::Json &JSON::Json::operator[](int32_t index) const
	{
		return this->operator[]((size_t) index);
	}
	
	JSON::Json &JSON::Json::operator[](int32_t index)
	{
		return this->operator[]((size_t) index);
	}
	
	JSON::Json &JSON::Json::operator[](const TCHAR *key) const
	{
		if (auto arr = PtrCast<JObject>(this->json))
		{
			return arr->values[key];
		}
		return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	JSON::Json &JSON::Json::operator[](const TCHAR *key)
	{
		if (auto arr = PtrCast<JObject>(this->json))
		{
			return arr->values[key];
		}
		if (!Is<GNull>()) return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
		auto arr = MakeShared<JObject>();
		
		JSON::Json buffer;
		this->json = arr;
		return arr->values[key] = buffer;
	}
	
	JSON::Json &JSON::Json::operator[](const TString &key) const
	{
		if (auto arr = PtrCast<JObject>(this->json))
		{
			return arr->values[key];
		}
		return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	JSON::Json &JSON::Json::operator[](const TString &key)
	{
		if (auto arr = PtrCast<JObject>(this->json))
		{
			return arr->values[key];
		}
		if (!Is<GNull>()) return errorJson = (__FUNCSIG__ TEXT(":: This is not an array"));
		TSharedPtr<JObject> arr;
		this->json = arr = MakeShared<JObject>();
		
		JSON::Json buffer;
		return arr->values[key] = buffer;
	}
	
	bool JSON::Json::operator==(const JSON::Json &_other)
	{
		return this->json == _other.json;
	}
	
	bool JSON::Json::operator!=(const JSON::Json &_other)
	{
		return this->json != _other.json;
	}
	
	void JSON::Json::Push(const Json &_json)
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			arr->values.push_back(_json);
			return;
		}
		if (!Is<GNull>()) throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
		auto arr = MakeShared<JArray>();
		arr->values.push_back(_json);
		this->json = arr;
	}
	
	void JSON::Json::Pop()
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			arr->values.pop_back();
			return;
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	bool JSON::Json::Has(size_t index) const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return index < arr->values.size();
		}
		return false;
	}
	
	bool JSON::Json::Has(const TString &key) const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.find(key) != obj->values.end();
		}
		return false;
	}
	
	JSON::Json::ArrayIterator JSON::Json::Remove(size_t index)
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			if (index >= arr->values.size()) throw EOutOfRangeException(__FUNCSIG__ TEXT(":: out of range"));
			return arr->values.erase(arr->values.begin() + index);
		}
		return {};
	}
	
	JSON::Json::ArrayIterator JSON::Json::Remove(const ArrayIterator &_First, const ArrayIterator &_Last)
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.erase(_First, _Last);
		}
		return {};
	}
	
	JSON::Json::ArrayIterator JSON::Json::Remove(const ArrayIterator &_Where)
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.erase(_Where);
		}
		return {};
	}
	
	size_t JSON::Json::Remove(const TString &key)
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.erase(key);
		}
		return 0;
	}
	
	JSON::Json::ObjectIterator JSON::Json::Remove(const ObjectIterator &_First, const ObjectIterator &_Last)
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.erase(_First, _Last);
		}
		return {};
	}
	
	JSON::Json::ObjectIterator JSON::Json::Remove(const ObjectIterator &_Where)
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.erase(_Where);
		}
		return {};
	}
	
	JSON::Json::ObjectIterator JSON::Json::begin() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.begin();
		}
		return {};
	}
	
	JSON::Json::ObjectIterator JSON::Json::end() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.end();
		}
		return {};
	}
	
	size_t JSON::Json::Size() const
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
	
	JSON::Json::ArrayIterator JSON::Json::ArrayBegin() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.begin();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	JSON::Json::ArrayIterator JSON::Json::ArrayEnd() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.end();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	JSON::Json::ArrayReverseIterator JSON::Json::ArrayRBegin() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.rbegin();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	JSON::Json::ArrayReverseIterator JSON::Json::ArrayREnd() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values.rend();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	JSON::Json::ObjectIterator JSON::Json::ObjectBegin() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.begin();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	JSON::Json::ObjectIterator JSON::Json::ObjectEnd() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.end();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	JSON::Json::ObjectReverseIterator JSON::Json::ObjectRBegin() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.rbegin();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	JSON::Json::ObjectReverseIterator JSON::Json::ObjectREnd() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values.rend();
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	JSON::Json::Array &JSON::Json::ToArray() const
	{
		if (auto arr = PtrCast<JArray>(this->json))
		{
			return arr->values;
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an array"));
	}
	
	JSON::Json::Object &JSON::Json::ToMap() const
	{
		if (auto obj = PtrCast<JObject>(this->json))
		{
			return obj->values;
		}
		throw EInvalidArgumentException(__FUNCSIG__ TEXT(":: This is not an object"));
	}
	
	void JSON::Json::Reset()
	{
		this->json = MakeShared<GNull>();
	}
	
	TString JSON::Json::ToString() const noexcept
	{
		return this->json->ToString();
	}
	
}