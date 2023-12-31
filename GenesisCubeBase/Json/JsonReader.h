#pragma once

#include "../Core/Header.h"

#include "Json.h"
#include "JArray.h"
#include "JObject.h"


namespace GenesisCube::JSON
{
	
	///
	/// json读取器
	///
	class JsonReader : public GObject
	{
	public:
		
		explicit JsonReader(TIStream &source);
		
		~JsonReader() override;
	
	public:
		
		///
		/// 是否读取到最后
		///
		[[nodiscard]]
		bool Eof() const;
		
		///
		/// \return good
		[[nodiscard]]
		bool Good() const;
		
		///
		/// 获取JSON
		/// \return
		TPtr<Json> Next();
	
	public:
		
		[[nodiscard]]
		GObject *Clone() const noexcept override;
		
		GCLASS_BODY(JsonReader)
	
	private:
		
		TPtr<JSON::Json> ReadArray();
		
		TPtr<JSON::Json> ReadObject();
		
		TString ReadString(TCHAR stopChar);
		
		bool NextChar();
		
		bool UnnextChar();
	
	private:
		
		TIStream &source;
		
		TCHAR ch = TEXT('\0');
		
	};
}
