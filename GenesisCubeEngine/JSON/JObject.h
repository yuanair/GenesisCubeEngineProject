#pragma once

#include "JSON.h"


namespace GenesisCubeEngine::JSON
{
	
	/// <summary>
	/// JSON对象
	/// </summary>
	class JObject : public GObject
	{
	public:
		
		JObject();
		
		~JObject() override;
	
	public:
		
		[[nodiscard]] JObject *Clone() const noexcept override;
		
		[[nodiscard]] TString ToString() const noexcept override;
	
	public:
		
		std::map<TString, Json> values;
		
	};
}
	
