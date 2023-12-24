//
// Created by admin on 2023/12/21.
//

#pragma once

#include "../Core/Header.h"
#include "../Core/FCore.h"
#include "../JSON/Json.h"

namespace GenesisCubeEngine
{
	
	///
	/// 语言
	///
	class GLanguage : public GObject
	{
	public:
		
		GLanguage();
		
		GLanguage(TString name, TString displayName);
		
		~GLanguage() override;
	
	public:
		
		///
		/// 从JSON加载
		/// \param json Json
		/// \return 是否成功
		bool LoadFromJson(const JSON::Json &json);
	
	public:
		
		[[nodiscard]]
		GLanguage *Clone() const noexcept override;
	
	public:
		
		///
		/// zh_cn, en_us, ...
		///
		TString name;
		
		///
		/// 简体中文, English, ...
		///
		TString displayName;
		
		///
		/// 键值对
		///
		std::map<TString, TString> values;
		
	};
	
}