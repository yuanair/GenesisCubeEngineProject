#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"

namespace GenesisCube
{
	///
	/// JSON浮点数
	///
	class GFloat : public GObject
	{
	public:
		
		GFloat() : value(0.0) {}
		
		explicit GFloat(double_t value) : value(value) {}
		
		~GFloat() override = default;
	
	public:
		
		[[nodiscard]] inline GFloat *Clone() const noexcept override { return new GFloat(this->value); }
		
		[[nodiscard]] inline TString ToString() const noexcept override { return ToTString(this->value); }
		
		[[nodiscard]] inline double_t Get() const noexcept { return this->value; }
	
	private:
		
		double_t value;
		
	};
}