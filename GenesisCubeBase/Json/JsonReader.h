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
		/// \return 获取
		inline TPtr<Json> NextSafe() { return Next(); }
		
		///
		/// \return good
		[[nodiscard]]
		bool Good() const;
		
		///
		/// 获取JSON
		/// \return
		Json *Next();
	
	public:
		
		[[nodiscard]]
		GObject *Clone() const noexcept override;
	
	private:
		
		Json *ReadArray();
		
		Json *ReadObject();
		
		TString ReadString(TCHAR stopChar);
		
		bool NextChar();
		
		bool UnnextChar();
	
	private:
		
		TIStream &source;
		
		TCHAR ch = TEXT('\0');
		
	};
}
