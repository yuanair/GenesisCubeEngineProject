#pragma once

#include "../Core/Header.h"
#include "GFileName.h"
#include "../Core/TEvent.h"

namespace GenesisCubeEngine
{
	/// <summary>
	/// 目录类
	/// </summary>
	class GDirectoryName : public GFileName
	{
	public:
		
		struct ForeachEventArgsBase
		{
			/// <summary>
			/// 文件
			/// </summary>
			TPtr<GFileName> fileName;
			
			/// <summary>
			/// 文件创建时间
			/// </summary>
			FILETIME creationTime{};
			
			/// <summary>
			/// 最后访问时间
			/// </summary>
			FILETIME lastAccessTime{};
			
			/// <summary>
			/// 最后写入时间
			/// </summary>
			FILETIME lastWriteTime{};
		};
		
		/// <summary>
		/// foreach事件参数
		/// </summary>
		struct ForeachEventArgs : public ForeachEventArgsBase
		{
			/// <summary>
			/// 调用者
			/// </summary>
			GDirectoryName &directory;
			
			explicit ForeachEventArgs(GDirectoryName &directory) : directory(directory) {}
			
		};
		
		/// <summary>
		/// foreach事件参数
		/// </summary>
		struct ConstForeachEventArgs : public ForeachEventArgsBase
		{
			/// <summary>
			/// 调用者
			/// </summary>
			const GDirectoryName &directory;
			
			explicit ConstForeachEventArgs(const GDirectoryName &directory) : directory(directory) {}
			
		};
	
	public:
		
		GDirectoryName();
		
		GDirectoryName(const GDirectoryName &_other);
		
		explicit GDirectoryName(const TString &directoryName);
		
		~GDirectoryName() override;
	
	public:
		
		GDirectoryName &operator=(const GDirectoryName &_other);
	
	public:
		
		/// <summary>
		/// 获取当前目录
		/// </summary>
		/// <returns>目录</returns>
		static GDirectoryName CurrentDirectory();
		
		/// <summary>
		/// 设置当前目录
		/// </summary>
		/// <returns>成功返回非零，失败返回零</returns>
		static BOOL CurrentDirectory(const GDirectoryName &directory);
		
		/// <summary>
		/// 查找文件夹下所有文件与目录。
		/// </summary>
		/// <param name="fileNames">文件数组</param>
		/// <returns>是否成功</returns>
		bool Find(std::vector<TPtr<GFileName>> &fileNames) const;
		
		/// <summary>
		/// 查找文件夹下所有文件与目录。
		/// </summary>
		/// <param name="_event">事件</param>
		/// <returns>是否成功</returns>
		[[nodiscard]]
		bool FindForeach(const TEvent<ConstForeachEventArgs> &_event) const;
		
		/// <summary>
		/// 查找文件夹下所有文件与目录。
		/// </summary>
		/// <param name="_event">事件</param>
		/// <returns>是否成功</returns>
		bool FindForeach(const TEvent<ForeachEventArgs> &_event);
		
		
	};
	
}
