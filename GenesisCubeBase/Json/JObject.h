#pragma once

#include "Json.h"


namespace GenesisCube::JSON
{
	
	///
	/// JSON对象
	///
	class JObject : public GObject
	{
	public:
		
		JObject();
		
		~JObject() override;
	
	public:
		
		[[nodiscard]]
		JObject *Clone() const noexcept override;
		
		[[nodiscard]]
		TString ToString() const noexcept override;
	
	public:
		
		std::map<TString, Json> values;
		
	};
}
	
