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
		
		///
		/// 从文件加载
		/// \param file 文件
		/// \param desiredChannels 期望的通道数
		FImageData(const TString &file, int32_t desiredChannels = 4);
		
		///
		/// 从文件加载
		/// \param pFile 文件
		/// \param desiredChannels 期望的通道数
		FImageData(FILE *pFile, int32_t desiredChannels = 4);
		
		~FImageData();
	
	public:
		
		///
		/// 从文件加载
		/// \param file 文件
		/// \param desiredChannels 期望的通道数
		void LoadFromFile(const TString &file, int32_t desiredChannels = 4);
		
		///
		/// 从文件加载
		/// \param pFile 文件
		/// \param desiredChannels 期望的通道数
		void LoadFromFile(FILE *pFile, int32_t desiredChannels = 4);
		
		///
		/// 重置
		///
		void Reset();
	
	public:
		
		///
		/// \return 好
		[[nodiscard]]
		inline bool Good() const { return this->data != nullptr; }
		
		///
		/// \return 坏
		[[nodiscard]]
		inline bool Bad() const { return this->data == nullptr; }
		
		///
		/// \return 数据
		[[nodiscard]]
		inline uint8_t *GetData() const { return this->data; }
		
		///
		/// \return 宽度
		[[nodiscard]]
		inline int32_t GetWidth() const { return this->width; }
		
		///
		/// \return 高度
		[[nodiscard]]
		inline int32_t GetHeight() const { return this->height; }
		
		///
		/// \return 通道数
		[[nodiscard]]
		inline int32_t GetN() const { return this->n; }
	
	private:
		
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
