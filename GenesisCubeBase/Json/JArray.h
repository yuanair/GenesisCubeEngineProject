#pragma once

#include "../Core/Header.h"
#include "Json.h"


namespace GenesisCube::Json
{
	
	///
	/// JSON数组
	///
	class JArray : public GObject
	{
	public:
		
		typedef std::vector<Json> ValueType;
	
	public:
		
		JArray() = default;
		
		~JArray() override = default;
	
	public:
		
		[[nodiscard]]
		JArray *Clone() const noexcept override;
		
		[[nodiscard]]
		TString ToString() const noexcept override;
	
	public:
		
		ValueType values;
		
	};
}
