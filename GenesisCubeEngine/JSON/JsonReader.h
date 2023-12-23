#pragma once

#include "../Core/Header.h"

#include "Json.h"
#include "../IO/IReader.h"
#include "JArray.h"
#include "JObject.h"


namespace GenesisCubeEngine::JSON
{
	
	/// <summary>
	/// json读取器
	/// </summary>
	class JsonReader : public GObject, public IReader
	{
	public:
		
		JsonReader();
		
		explicit JsonReader(const TString &source);
		
		~JsonReader() override;
	
	public:
		
		/// <summary>
		/// 是否读取到最后
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] bool Final() const;
	
	public:
		
		// 通过 IReader 继承
		[[nodiscard]] bool Good() const override;
		
		Json *Next() override;
		
		[[nodiscard]] GObject *Clone() const noexcept override;
	
	private:
		
		Json *ReadArray();
		
		Json *ReadObject();
		
		TString ReadString(TCHAR stopChar);
		
		bool NextChar();
		
		bool UnnextChar();
	
	private:
		
		TString source;
		
		TCHAR ch = TEXT('\0');
		
		size_t index;
		
	};
}
