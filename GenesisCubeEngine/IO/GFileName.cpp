#include "GFileName.h"

#include "GDirectoryName.h"

namespace GenesisCubeEngine
{
	
	
	GFileName::GFileName(TString fileName)
		: fileName(std::move(fileName))
	{
	
	}
	
	
	GFileName GFileName::ModuleFile()
	{
		TCHAR lpFileName[MAX_PATH];
		::GetModuleFileName(nullptr, lpFileName, MAX_PATH);
		return GFileName(lpFileName);
	}
	
	bool GFileName::Find(const TString &fileName, std::vector<TPtr<GFileName>> &fileNames)
	{
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(fileName.c_str(), &fd);
		
		if (hFind == INVALID_HANDLE_VALUE) return false;
		
		do
		{
			if (!lstrcmp(fd.cFileName, TEXT(".")) || !lstrcmp(fd.cFileName, TEXT(".."))) continue;
			// 如果为目录
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				fileNames.push_back(new GDirectoryName(fd.cFileName));
			}
				// 如果为文件
			else
			{
				fileNames.push_back(new GFileName(fd.cFileName));
			}
		}
		while (::FindNextFile(hFind, &fd));
		
		::FindClose(hFind);
		return true;
	}
	
	bool GFileName::DragQuery(HDROP hDrop, std::vector<TPtr<GFileName>> &fileNames)
	{
		UINT nFileCount = ::DragQueryFile(hDrop, (UINT) -1, nullptr, 0);
		TCHAR szFileName[MAX_PATH] = {};
		DWORD dwAttribute;
		
		// 获取拖拽进来文件和文件夹
		for (UINT i = 0; i < nFileCount; i++)
		{
			::DragQueryFile(hDrop, i, szFileName, sizeof(szFileName) / sizeof(szFileName[0]));
			dwAttribute = ::GetFileAttributes(szFileName);
			
			// 是否为文件夹
			if (dwAttribute & FILE_ATTRIBUTE_DIRECTORY)
			{
				fileNames.push_back(new GDirectoryName(szFileName));
			}
			else
			{
				fileNames.push_back(new GFileName(szFileName));
			}
		}
		return true;
	}
	
}
