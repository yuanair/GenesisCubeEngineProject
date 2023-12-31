#include "GDirectoryName.h"

namespace GenesisCube
{
	GDirectoryName::GDirectoryName()
	= default;
	
	GDirectoryName::GDirectoryName(const GDirectoryName &_other)
		: GFileName(_other.fileName)
	{
	
	}
	
	GDirectoryName::GDirectoryName(const TString &directoryName)
		: GFileName(directoryName)
	{
	}
	
	GDirectoryName::~GDirectoryName()
	= default;
	
	GDirectoryName &GDirectoryName::operator=(const GDirectoryName &_other)
	{
		this->fileName = _other.fileName;
		return *this;
	}
	
	GDirectoryName GDirectoryName::CurrentDirectory()
	{
		GDirectoryName result;
		
		DWORD bufferSize = ::GetCurrentDirectory(0, NULL);
		TCHAR *lpDir = new TCHAR[bufferSize];
		
		::GetCurrentDirectory(bufferSize, lpDir);
		result.fileName = lpDir;
		
		delete[] lpDir;
		
		return result;
	}
	
	BOOL GDirectoryName::CurrentDirectory(const GDirectoryName &directory)
	{
		return ::SetCurrentDirectory(directory.fileName.c_str());
	}
	
	
	bool GDirectoryName::Find(std::list<TPtr<GFileName>> &fileNames) const
	{
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile((fileName + TEXT("\\*.*")).c_str(), &fd);
		
		if (hFind == INVALID_HANDLE_VALUE) return false;
		
		do
		{
			if (!lstrcmp(fd.cFileName, TEXT(".")) || !lstrcmp(fd.cFileName, TEXT(".."))) continue;
			// 如果为目录
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				fileNames.push_back(MakePtr<GDirectoryName>(fileName + TEXT("\\") + fd.cFileName));
			}
				// 如果为文件
			else
			{
				fileNames.push_back(MakePtr<GFileName>(fileName + TEXT("\\") + fd.cFileName));
			}
		}
		while (::FindNextFile(hFind, &fd));
		
		::FindClose(hFind);
		return true;
	}
	
	bool GDirectoryName::FindForeach(const TEvent<ConstForeachEventArgs> &_event) const
	{
		WIN32_FIND_DATA fd;
		ConstForeachEventArgs args(*this);
		HANDLE hFind = ::FindFirstFile((fileName + TEXT("\\*.*")).c_str(), &fd);
		
		if (hFind == INVALID_HANDLE_VALUE) return false;
		
		do
		{
			if (!lstrcmp(fd.cFileName, TEXT(".")) || !lstrcmp(fd.cFileName, TEXT(".."))) continue;
			args.creationTime = fd.ftCreationTime;
			args.lastAccessTime = fd.ftLastAccessTime;
			args.lastWriteTime = fd.ftLastWriteTime;
			// 如果为目录
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				args.fileName = MakePtr<GDirectoryName>(fileName + TEXT("\\") + fd.cFileName);
			}
				// 如果为文件
			else
			{
				args.fileName = MakePtr<GFileName>(fileName + TEXT("\\") + fd.cFileName);
			}
			_event.Trigger(args);
		}
		while (::FindNextFile(hFind, &fd));
		
		::FindClose(hFind);
		return true;
	}
	
	bool GDirectoryName::FindForeach(const TEvent<ForeachEventArgs> &_event)
	{
		WIN32_FIND_DATA fd;
		ForeachEventArgs args(*this);
		HANDLE hFind = ::FindFirstFile((fileName + TEXT("\\*.*")).c_str(), &fd);
		
		if (hFind == INVALID_HANDLE_VALUE) return false;
		
		do
		{
			if (!lstrcmp(fd.cFileName, TEXT(".")) || !lstrcmp(fd.cFileName, TEXT(".."))) continue;
			args.creationTime = fd.ftCreationTime;
			args.lastAccessTime = fd.ftLastAccessTime;
			args.lastWriteTime = fd.ftLastWriteTime;
			// 如果为目录
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				args.fileName = MakePtr<GDirectoryName>(fileName + TEXT("\\") + fd.cFileName);
			}
				// 如果为文件
			else
			{
				args.fileName = MakePtr<GFileName>(fileName + TEXT("\\") + fd.cFileName);
			}
			_event.Trigger(args);
		}
		while (::FindNextFile(hFind, &fd));
		
		::FindClose(hFind);
		return true;
	}
	
}
