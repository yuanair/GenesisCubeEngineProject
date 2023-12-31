#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"

namespace GenesisCube
{
	/// 
	/// 布尔
	/// 
	class GBool : public GObject
	{
	public:
		
		GBool() : value(false) {}
		
		explicit GBool(bool value) : value(value) {}
		
		~GBool() override = default;
	
	public:
		
		[[nodiscard]]
		inline GBool *Clone() const noexcept override { return new GBool(this->value); }
		
		GCLASS_BODY(GBool)
		
		[[nodiscard]]
		inline TString ToString() const noexcept override
		{
			return this->value ? TEXT("true") : TEXT("false");
		}
		
		[[nodiscard]]
		inline bool Get() const noexcept { return this->value; }
	
	private:
		
		bool value;
		
	};
}