//
// Created by admin on 2023/12/19.
//

#pragma once

#include "../Core/Header.h"
#include "../Core/FCore.h"

namespace GenesisCube
{
	
	template<class T>
	struct FClamp
	{
		// 最小值
		T minValue;
		
		// 最大值
		T maxValue;
		
		// 限制
		inline T Clamp(T value) const
		{
			return value > maxValue ? maxValue : (value < minValue ? minValue : value);
		}
		
	};
	
	template<class T>
	struct FSize
	{
		// 宽度
		T width;
		
		// 高度
		T height;
		
	};
	
	template<class T>
	struct FSizeClamp
	{
		// 宽度
		FSize<T> minSize;
		
		// 高度
		FSize<T> maxSize;
		
		// 限制
		inline FSize<T> Clamp(FSize<T> size) const
		{
			FSize<T> result =
				{
					.width=size.width > maxSize.width ? maxSize.width : (
						size.width < minSize.width ? minSize.width : size.width
					),
					.height=size.height > maxSize.height ? maxSize.height : (
						size.height < minSize.height ? minSize.height : size.height
					)
				};
			return result;
		}
		
	};
	
	template<class T>
	struct FRect
	{
		// x坐标
		T x;
		
		// y坐标
		T y;
		
		// 宽度
		T width;
		
		// 高度
		T height;
		
	};
	
	
} // GenesisCube

namespace std
{
	
	
	template<class T>
	struct std::formatter<GenesisCube::FSize < T>, GenesisCube::TChar>
		: formatter<T, GenesisCube::TChar>
	{
		
		template<class C>
		constexpr auto format(const GenesisCube::FSize<T> &rect, C &context)
		{
			typename C::iterator Ite = format_to(context.out(), TEXT("("));
			Ite = formatter<T, GenesisCube::TChar>::format(rect.width, context);
			Ite = TEXT(',');
			Ite = TEXT(' ');
			Ite = formatter<T, GenesisCube::TChar>::format(rect.height, context);
			Ite = TEXT(')');
			return Ite;
		}
		
	};
	
	template<class T>
	struct std::formatter<GenesisCube::FRect<T>, GenesisCube::TChar>
		: formatter<T, GenesisCube::TChar>
	{
		
		template<class C>
		constexpr auto format(const GenesisCube::FRect<T> &rect, C &context)
		{
			typename C::iterator Ite = format_to(context.out(), TEXT("("));
			Ite = formatter<T, GenesisCube::TChar>::format(rect.x, context);
			Ite = TEXT(',');
			Ite = TEXT(' ');
			Ite = formatter<T, GenesisCube::TChar>::format(rect.y, context);
			Ite = TEXT(',');
			Ite = TEXT(' ');
			Ite = formatter<T, GenesisCube::TChar>::format(rect.width, context);
			Ite = TEXT(',');
			Ite = TEXT(' ');
			Ite = formatter<T, GenesisCube::TChar>::format(rect.height, context);
			Ite = TEXT(')');
			return Ite;
		}
		
	};
}