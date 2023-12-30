//
// Created by admin on 2023/12/21.
//
#include "Localization.h"
#include "../../GenesisCubeBase/JSON/JObject.h"

namespace GenesisCube
{


//	TString GLanguage::Find(const GenesisCube::GStringList &list,
//							const GenesisCube::TString &key,
//							const GenesisCube::GLanguage *language)
//	{
//		auto string = list.find(key);
//		if (string == list.end()) return key;
//		auto value = string->second.find(language);
//		if (value == string->second.end()) return key;
//		return value->second;
//	}
	
	bool GLanguage::LoadFromJson(const JSON::Json &json)
	{
		this->name.clear();
		this->displayName.clear();
		this->values.clear();
		if (!json.Is<JSON::JObject>()) return false;
		for (auto iter = json.ObjectBegin(); iter != json.ObjectEnd(); iter++)
		{
			if (iter->second.Is<GString>())
			{
				TString buffer = iter->second.operator TString();
				if (iter->first == TEXT("name"))
				{
					this->name = buffer;
				}
				else if (iter->first == TEXT("displayName"))
				{
					this->displayName = buffer;
				}
				else
				{
					this->values[iter->first] = buffer;
				}
			}
		}
		return true;
	}
	
	GLanguage *GLanguage::Clone() const noexcept
	{
		auto ptr = new GLanguage(this->name, this->displayName);
		ptr->values = this->values;
		return ptr;
	}
	
	GLanguage::GLanguage()
	= default;
	
	GLanguage::~GLanguage()
	= default;
	
	GLanguage::GLanguage(TString name, TString displayName)
		: name(std::move(name)), displayName(std::move(displayName))
	{
	
	}
}