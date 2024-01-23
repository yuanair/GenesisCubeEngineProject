#pragma once

#include "Json.h"


namespace GenesisCube::Json
{
	
	///
	/// JSON对象
	///
	class JObject : public GObject
	{
	public:
		
		typedef std::map<TString, Json> ValueType;
	
	public:
		
		JObject() = default;
		
		~JObject() override = default;
	
	public:
		
		[[nodiscard]]
		JObject *Clone() const noexcept override;
		
		[[nodiscard]]
		TString ToString() const noexcept override;
	
	public:
		
		ValueType values;
		
	};
}
	
