#pragma once

#include "../Core/Header.h"
#include "JSON.h"

namespace GenesisCubeEngine
{
	namespace JSON
	{
		
		/// <summary>
		/// JSON数组
		/// </summary>
		class JArray : public GObject
		{
		public:
			
			JArray() {}
			
			~JArray() override {}
		
		public:
			
			JArray *Clone() const noexcept override;
			
			TString ToString() const noexcept override;
		
		public:
			
			std::vector<Json> values;
			
		};
	}
}