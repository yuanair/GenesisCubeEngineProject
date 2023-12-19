#pragma once

#include "../Core/GenesisCubeEngine.h"
#include "GFileName.h"


namespace GenesisCubeEngine
{
	/// <summary>
	/// 文件类
	/// </summary>
	class GFile : public GFileName
	{
	public:

		GFile();

		GFile(const GFile& _other);

		explicit GFile(const TString& fileName);

		~GFile() override;

	public:

		GFile& operator=(const GFile& _other);

	public:

		/// <summary>
		/// 模块所在文件
		/// </summary>
		/// <returns>文件</returns>
		static GFile ModuleFile();

		/// <summary>
		/// 查找文件。可以包含通配符，例如星号'*'或问号'?'。
		/// </summary>
		/// <param name="fileName">文件名</param>
		/// <param name="fileNames">文件数组</param>
		/// <returns>文件数组</returns>
		static bool Find(const TString& fileName, std::vector<TPtr<GFileName>>& fileNames);

		/// <summary>
		/// 拖放文件查找
		/// </summary>
		/// <param name="hDrop"></param>
		/// <param name="fileNames">文件数组</param>
		/// <returns>是否成功</returns>
		static bool DragQuery(HDROP hDrop, std::vector<TPtr<GFileName>>& fileNames);

	};

}