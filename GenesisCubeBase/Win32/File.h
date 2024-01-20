//
// Created by admin on 2024/1/20.
//

#pragma once

#include "../Core/Header.h"
#include "../Core/FCore.h"
#include "../IO/IReader.h"

namespace GenesisCube::Win32
{
	///
	/// 读取器
	class FDragQueryFileReader
	{
	public:
		
		FDragQueryFileReader(HDROP hDrop);
		
		~FDragQueryFileReader();
	
	public:
		
		///
		/// \param value 文件名
		/// \param index 索引
		bool Get(TString &value, size_t index);
		
		///
		/// \return 文件数量
		[[nodiscard]]
		inline uint32_t GetFileCount() const noexcept { return this->nFileCount; }
	
	private:
		
		HDROP hDrop;
		
		uint32_t nFileCount;
		
	};
	
	
	///
	/// 读取器
	class FFileFinder
	{
	public:
		
		FFileFinder();
		
		~FFileFinder();
	
	public:
		
		///
		/// \param value 文件数据
		/// \param fileName 文件名，支持通配符
		/// \return 是否成功
		bool Find(WIN32_FIND_DATA &value, const TString &fileName);
		
		///
		/// \param value 文件数据
		/// \return 是否成功
		bool Next(WIN32_FIND_DATA &value);
		
		///
		/// 关闭
		/// \return 是否成功
		bool Close();
	
	private:
		
		HANDLE handle;
		
	};
	
	///
	/// \param fileName 文件
	/// \return 属性
	DWORD GetFileAttributesT(const TString &fileName);
	
	///
	/// \param fileAttributes 文件属性
	/// \return 是否为文件夹
	bool IsDirectory(DWORD fileAttributes);
	
	///
	/// \param fileName 文件
	/// \return 是否为文件夹
	inline bool IsDirectory(const TString &fileName) { return IsDirectory(GetFileAttributesT(fileName)); }
	
	///
	/// \param hModule 模块
	/// \return 模块名
	TString GetModuleFileNameT(HMODULE hModule = nullptr);
	
	///
	/// 获取当前路径
	TString GetCurrentDirectoryT();
	
	///
	/// 设置当前路径
	/// \param pathName 路径
	/// \return 是否成功
	bool SetCurrentDirectoryT(const TString &pathName);
	
} // GenesisCube
