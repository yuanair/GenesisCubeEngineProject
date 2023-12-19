#include "GDirectory.h"
#include "GFile.h"

namespace GenesisCubeEngine
{
	GDirectory::GDirectory()
	= default;

	GDirectory::GDirectory(const GDirectory& _other)
		: GFileName(_other.fileName)
	{

	}

	GDirectory::GDirectory(const TString& directoryName)
		: GFileName(directoryName)
	{
	}

	GDirectory::~GDirectory()
	= default;

	GDirectory& GDirectory::operator=(const GDirectory& _other)
	{
		this->fileName = _other.fileName;
		return *this;
	}

	GDirectory GDirectory::CurrentDirectory()
	{
		GDirectory result;
		
		DWORD bufferSize = ::GetCurrentDirectory(0, NULL);
		TCHAR* lpDir = new TCHAR[bufferSize];
		
		::GetCurrentDirectory(bufferSize, lpDir);
		result.fileName = lpDir;
		
		delete[] lpDir;

		return result;
	}

	BOOL GDirectory::CurrentDirectory(const GDirectory& directory)
	{
		return ::SetCurrentDirectory(directory.fileName.c_str());
	}


	bool GDirectory::Find(std::vector<TPtr<GFileName>>& fileNames) const
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
				fileNames.push_back(new GDirectory(fileName + TEXT("\\") + fd.cFileName));
			}
			// 如果为文件
			else
			{
				fileNames.push_back(new GFile(fileName + TEXT("\\") + fd.cFileName));
			}
		}
		while (::FindNextFile(hFind, &fd));

		::FindClose(hFind);
		return true;
	}

	bool GDirectory::FindForeach(const TEvent<ConstForeachEventArgs>& _event) const
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
				args.fileName = new GDirectory(fileName + TEXT("\\") + fd.cFileName);
			}
			// 如果为文件
			else
			{
				args.fileName = new GFile(fileName + TEXT("\\") + fd.cFileName);
			}
			_event.Trigger(args);
		}
		while (::FindNextFile(hFind, &fd));

		::FindClose(hFind);
		return true;
	}

	bool GDirectory::FindForeach(const TEvent<ForeachEventArgs>& _event)
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
				args.fileName = new GDirectory(fileName + TEXT("\\") + fd.cFileName);
			}
			// 如果为文件
			else
			{
				args.fileName = new GFile(fileName + TEXT("\\") + fd.cFileName);
			}
			_event.Trigger(args);
		}
		while (::FindNextFile(hFind, &fd));

		::FindClose(hFind);
		return true;
	}

}
