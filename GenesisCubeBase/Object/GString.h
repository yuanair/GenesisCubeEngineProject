#pragma once

#include "../Core/Header.h"

#include "../Object/GObject.h"

namespace GenesisCube
{
	///
	/// 字符串
	///
	class GString : public GObject
	{
	public:
		
		typedef TString ValueType;
	
	public:
		
		GString() : str() {}
		
		explicit GString(TString str) : str(std::move(str)) {}
		
		explicit GString(const TCHAR *str) : str(str) {}
		
		~GString() override = default;
	
	public:
		
		[[nodiscard]]
		inline GString *Clone() const noexcept override { return new GString(this->str); }
		
		GCLASS_BODY(GString)
		
		[[nodiscard]]
		TString ToString() const noexcept override;
		
		[[nodiscard]]
		inline TString Get() const noexcept { return this->str; }
	
	private:
		
		TString str;
		
	};
}