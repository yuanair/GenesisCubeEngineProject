#pragma once

#include "../Core/Header.h"
#include <utility>

#include "../Object/GObject.h"

namespace GenesisCubeEngine
{
	/// <summary>
	/// JSON字符串
	/// </summary>
	class GString : public GObject
	{
	public:
		
		GString() : str() {}
		
		explicit GString(TString str) : str(std::move(str)) {}
		
		explicit GString(const TCHAR *str) : str(str) {}
		
		~GString() override = default;
	
	public:
		
		[[nodiscard]] inline GString *Clone() const noexcept override { return new GString(this->str); }
		
		[[nodiscard]] TString ToString() const noexcept override;
		
		[[nodiscard]] inline TString Get() const noexcept { return this->str; }
	
	private:
		
		TString str;
		
	};
}