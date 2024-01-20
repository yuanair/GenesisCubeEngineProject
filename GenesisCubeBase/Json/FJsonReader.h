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
	class FJsonReader
	{
	public:
		
		explicit FJsonReader(TIStream &source);
		
		~FJsonReader();
	
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
		TSharedPtr<Json> Next();
	
	private:
		
		TSharedPtr<JSON::Json> ReadArray();
		
		TSharedPtr<JSON::Json> ReadObject();
		
		TString ReadString(TCHAR stopChar);
		
		bool NextChar();
		
		bool UnnextChar();
	
	private:
		
		TIStream &source;
		
		TCHAR ch;
		
	};
}
