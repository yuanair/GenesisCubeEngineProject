//
// Created by admin on 2024/1/13.
//

#pragma once

#include "FCore.h"

namespace GenesisCube
{
	
	
	///
	/// 点
	/// \tparam T 类型
	template<class T>
	struct TPoint2
	{
		/// 横坐标
		T x;
		
		/// 纵坐标
		T y;
	};
	
	
	///
	/// 大小
	/// \tparam T 类型
	template<class T>
	struct TSize2
	{
		/// 宽
		T width;
		
		/// 高
		T height;
	};
	
	
	///
	/// 点
	/// \tparam T 类型
	template<class T>
	struct TPoint3
	{
		/// 前后向坐标
		T x;
		
		/// 左右向坐标
		T y;
		
		/// 垂直坐标
		T z;
	};
	
	
	///
	/// 大小
	/// \tparam T 类型
	template<class T>
	struct TSize3
	{
		///
		T x;
		
		///
		T y;
		
		/// 高
		T z;
	};
	
	
	///
	/// 矩形
	/// \tparam T 类型
	template<class T>
	struct TRect
	{
		/// 横坐标
		T x;
		
		/// 纵坐标
		T y;
		
		/// 宽
		T width;
		
		/// 高
		T height;
		
		///
		/// \return 位置
		inline TSize2<T> GetPoint() const noexcept { return TPoint2<T>{x, y}; }
		
		///
		/// \return 中心点
		inline TSize2<T> GetCenterPoint() const noexcept { return TPoint2<T>{x + width / 2, y + height / 2}; }
		
		///
		/// \return 大小
		inline TSize2<T> GetSize() const noexcept { return TSize2<T>{width, height}; }
		
	};
	
	typedef TRect<int32_t> FRectI;
	typedef TRect<uint32_t> FRectU;
	typedef TRect<float_t> FRectF;
	typedef TRect<double_t> FRectD;
	
	typedef TPoint2<int32_t> FPoint2I;
	typedef TPoint2<uint32_t> FPoint2U;
	typedef TPoint2<float_t> FPoint2F;
	typedef TPoint2<double_t> FPoint2D;
	
	typedef TSize2<int32_t> FSize2I;
	typedef TSize2<uint32_t> FSize2U;
	typedef TSize2<float_t> FSize2F;
	typedef TSize2<double_t> FSize2D;
	
	typedef TPoint3<int32_t> FPoint3I;
	typedef TPoint3<uint32_t> FPoint3U;
	typedef TPoint3<float_t> FPoint3F;
	typedef TPoint3<double_t> FPoint3D;
	
	typedef TSize3<int32_t> FSize3I;
	typedef TSize3<uint32_t> FSize3U;
	typedef TSize3<float_t> FSize3F;
	typedef TSize3<double_t> FSize3D;
	
	
} // GenesisCube
