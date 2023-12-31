﻿#pragma once

#include "../Core/Header.h"
#include "Json.h"


namespace GenesisCube::JSON
{
	
	///
	/// JSON数组
	///
	class JArray : public GObject
	{
	public:
		
		JArray() = default;
		
		~JArray() override = default;
	
	public:
		
		[[nodiscard]] JArray *Clone() const noexcept override;
		
		GCLASS_BODY(JArray)
		
		[[nodiscard]] TString ToString() const noexcept override;
	
	public:
		
		std::vector<Json> values;
		
	};
}
