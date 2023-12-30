//
// Created by admin on 2023/12/27.
//

#pragma once

#include "../Core/Header.h"
#include "../Core/FCore.h"

namespace GenesisCube
{
	///
	/// 图片数据
	///
	class FImageData
	{
	public:
		
		FImageData();
		
		~FImageData();
	
	public:
		
		///
		/// 从文件加载
		/// \param file 文件
		/// \param desiredChannels 期望的通道数
		/// \return 是否成功
		bool LoadFromFile(const TString &file, int32_t desiredChannels = 4);
		
		///
		/// 从文件加载
		/// \param pFile 文件
		/// \param desiredChannels 期望的通道数
		/// \return 是否成功
		bool LoadFromFile(FILE *pFile, int32_t desiredChannels = 4);
		
		///
		/// 重置
		///
		void Reset();
	
	public:
		
		///
		/// 数据
		///
		uint8_t *data;
		
		///
		/// 宽度
		///
		int32_t width;
		
		///
		/// 高度
		///
		int32_t height;
		
		///
		/// RGB -> 3
		/// RGBA -> 4
		/// 通道数
		///
		int32_t n;
		
	};
	
} // GenesisCube
