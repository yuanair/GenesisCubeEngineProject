#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"

namespace GenesisCubeEngine
{
	///
	/// JSON对象
	///
	class GNull : public GObject
	{
	public:
		
		GNull() = default;
		
		explicit GNull(nullptr_t) {}
		
		~GNull() override = default;
	
	public:
		
		[[nodiscard]] inline GNull *Clone() const noexcept override { return new GNull(); }
		
		[[nodiscard]] inline TString ToString() const noexcept override { return TEXT("null"); }
		
		[[nodiscard]] static inline nullptr_t Get() noexcept { return {}; }
		
	};
}