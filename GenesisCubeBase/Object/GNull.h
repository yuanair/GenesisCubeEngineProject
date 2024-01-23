#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"

namespace GenesisCube
{
	///
	/// null
	///
	class GNull : public GObject
	{
	public:
		
		typedef nullptr_t ValueType;
	
	public:
		
		GNull() = default;
		
		explicit GNull(nullptr_t) {}
		
		~GNull() override = default;
	
	public:
		
		[[nodiscard]]
		inline GNull *Clone() const noexcept override { return new GNull(); }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("null"); }
		
		[[nodiscard]]
		static inline nullptr_t Get() noexcept { return {}; }
		
	};
}