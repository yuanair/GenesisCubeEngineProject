#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"
#include "../Core/TPtr.h"

namespace GenesisCubeEngine
{
	/// <summary>
	/// 文件名类
	/// </summary>
	class GFileName : public GObject
	{
	public:
		
		GFileName() = default;
		
		explicit GFileName(TString fileName);
		
		~GFileName() override = default;
	
	public:
		
		/// <summary>
		/// 模块所在文件
		/// </summary>
		/// <returns>文件</returns>
		static GFileName ModuleFile();
		
		/// <summary>
		/// 查找文件。可以包含通配符，例如星号'*'或问号'?'。
		/// </summary>
		/// <param name="fileName">文件名</param>
		/// <param name="fileNames">文件数组</param>
		/// <returns>文件数组</returns>
		static bool Find(const TString &fileName, std::list<TPtr<GFileName>> &fileNames);
		
		/// <summary>
		/// 拖放文件查找
		/// </summary>
		/// <param name="hDrop"></param>
		/// <param name="fileNames">文件数组</param>
		/// <returns>是否成功</returns>
		static bool DragQuery(HDROP hDrop, std::list<TPtr<GFileName>> &fileNames);
		
		
		/// <summary>
		/// 设置文件名
		/// </summary>
		/// <param name="_fileName">文件名</param>
		inline virtual void SetFileName(const TString &_fileName) { this->fileName = _fileName; }
	
	public:
		
		/// <summary>
		/// 克隆
		/// </summary>
		/// <returns></returns>
		[[nodiscard]]
		inline GFileName *Clone() const noexcept override { return new GFileName(this->fileName); }
		
		/// <summary>
		/// 获取文件名
		/// </summary>
		/// <returns>文件名</returns>
		[[nodiscard]]
		inline const TString &GetFileName() const noexcept { return this->fileName; }
	
	protected:
		
		TString fileName;
		
	};
	
}