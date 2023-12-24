#pragma once

#include "../Core/Header.h"

#include "Json.h"
#include "../IO/IReader.h"
#include "JArray.h"
#include "JObject.h"


namespace GenesisCubeEngine::JSON
{
	
	///
	/// json读取器
	///
	class JsonReader : public GObject, public IReader
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
	
	public:
		
		/// 通过 IReader 继承
		[[nodiscard]]
		bool Good() const override;
		
		Json *Next() override;
		
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
