﻿#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"

namespace GenesisCube
{
	///
	/// 整数
	///
	class GInteger : public GObject
	{
	public:
		
		typedef int64_t ValueType;
	
	public:
		
		GInteger() : value(0) {}
		
		explicit GInteger(int64_t value) : value(value) {}
		
		~GInteger() override = default;
	
	public:
		
		[[nodiscard]]
		inline GInteger *Clone() const noexcept override { return new GInteger(this->value); }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return ToTString(this->value); }
		
		[[nodiscard]]
		inline int64_t Get() const noexcept { return this->value; }
	
	private:
		
		int64_t value;
		
	};
}