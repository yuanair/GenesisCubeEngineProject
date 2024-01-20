//
// Created by admin on 2024/1/20.
//

#include "File.h"

namespace GenesisCube::Win32
{
	
	TString GetCurrentDirectoryT()
	{
		DWORD bufferSize = ::GetCurrentDirectory(0, nullptr);
		auto lpDir = new TCHAR[bufferSize];
		
		if (!::GetCurrentDirectory(bufferSize, lpDir))
		{
			delete[] lpDir;
			return {};
		}
		TString result = lpDir;
		
		delete[] lpDir;
		return result;
	}
	
	bool SetCurrentDirectoryT(const TString &pathName)
	{
		return ::SetCurrentDirectory(pathName.c_str());
	}
	
	DWORD GetFileAttributesT(const TString &fileName)
	{
		return ::GetFileAttributes(fileName.c_str());
	}
	
	bool IsDirectory(DWORD fileAttributes)
	{
		return fileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	}
	
	TString GetModuleFileNameT(HMODULE hModule)
	{
		TChar buffer[MAX_PATH];
		if (!::GetModuleFileName(hModule, buffer, MAX_PATH))return {};
		return buffer;
	}
	
	FDragQueryFileReader::~FDragQueryFileReader()
	{
	
	}
	
	FDragQueryFileReader::FDragQueryFileReader(HDROP hDrop)
		: hDrop(hDrop), nFileCount(::DragQueryFile(hDrop, (UINT) -1, nullptr, 0))
	{
	
	}
	
	bool FDragQueryFileReader::Get(TString &value, size_t index)
	{
		if (index >= nFileCount) return false;
		UINT length = ::DragQueryFile(hDrop, (UINT) index, nullptr, 0) + 1;
		auto fileName = new TChar[length];
		if (!::DragQueryFile(hDrop, (UINT) index, fileName, length))
		{
			delete[] fileName;
			return false;
		}
		value = fileName;
		delete[] fileName;
		return true;
	}
	
	FFileFinder::FFileFinder()
		: handle(INVALID_HANDLE_VALUE)
	{
	
	}
	
	FFileFinder::~FFileFinder()
	{
		Close();
	}
	
	bool FFileFinder::Find(WIN32_FIND_DATA &value, const TString &fileName)
	{
		Close();;
		return INVALID_HANDLE_VALUE != (this->handle = ::FindFirstFile(fileName.c_str(), &value));
	}
	
	bool FFileFinder::Next(WIN32_FIND_DATA &value)
	{
		return ::FindNextFile(handle, &value);
	}
	
	bool FFileFinder::Close()
	{
		if (handle == INVALID_HANDLE_VALUE) return true;
		bool result = ::FindClose(handle);
		handle = INVALID_HANDLE_VALUE;
		return result;
	}
} // GenesisCube