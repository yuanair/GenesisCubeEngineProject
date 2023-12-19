#include "GFile.h"
#include "GDirectory.h"

namespace GenesisCubeEngine
{

	GFile::GFile()
	{

	}

	GFile::GFile(const GFile& _other)
		: GFileName(_other.fileName)
	{

	}

	GFile::GFile(const TString& directoryName)
		: GFileName(directoryName)
	{
	}

	GFile::~GFile()
	{

	}

	GFile& GFile::operator=(const GFile& _other)
	{
		this->fileName = _other.fileName;
		return *this;
	}

	GFile GFile::ModuleFile()
	{
		TCHAR lpFileName[MAX_PATH];
		::GetModuleFileName(NULL, lpFileName, MAX_PATH);
		return GFile(lpFileName);
	}

	bool GFile::Find(const TString& fileName, std::vector<TPtr<GFileName>>& fileNames)
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
				fileNames.push_back(new GDirectory(fd.cFileName));
			}
			// 如果为文件
			else
			{
				fileNames.push_back(new GFile(fd.cFileName));
			}
		} while (::FindNextFile(hFind, &fd));

		::FindClose(hFind);
		return true;
	}

	bool GFile::DragQuery(HDROP hDrop, std::vector<TPtr<GFileName>>& fileNames)
	{
		UINT nFileCount = ::DragQueryFile(hDrop, (UINT)-1, NULL, 0);
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
				fileNames.push_back(new GDirectory(szFileName));
			}
			else
			{
				fileNames.push_back(new GFile(szFileName));
			}
		}
		return true;
	}


}
