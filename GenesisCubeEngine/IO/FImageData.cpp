//
// Created by admin on 2023/12/27.
//

#include "FImageData.h"
#include "../../GenesisCubeBase/Core/Debug.h"
#include "../includes/stb_image.h"

namespace GenesisCube
{
	FImageData::FImageData()
		: data(nullptr), width(0), height(0), n(0)
	{
	
	}
	
	FImageData::~FImageData()
	{
		Reset();
	}
	
	void FImageData::LoadFromFile(const TString &file, int32_t desiredChannels)
	{
		Reset();
		FILE *pFile;
#ifdef UNICODE
		_wfopen_s
#else
			fopen_s
#endif
			(&pFile, file.c_str(), TEXT("rb"));
		if (pFile == nullptr)
			return FLogger::Inst().LogErrorODS(std::format(TEXT("can not to open file \"{}\""), file));
		this->data = stbi_load_from_file(pFile, &this->width, &this->height, &this->n, desiredChannels);
		fclose(pFile);
		if (this->data == nullptr)
			return FLogger::Inst().LogErrorODS(
				std::format(TEXT("can not to load file \"{}\"(FILE 0x{:016X})"), file, (uintptr_t) pFile));
	}
	
	void FImageData::LoadFromFile(FILE *pFile, int32_t desiredChannels)
	{
		Reset();
		if (pFile == nullptr)
			return FLogger::Inst().LogErrorODS(std::format(TEXT("can not to load FILE(0x{:016X})"), (uintptr_t) pFile));
		this->data = stbi_load_from_file(pFile, &this->width, &this->height, &this->n, desiredChannels);
		if (this->data == nullptr)
			return FLogger::Inst().LogErrorODS(std::format(TEXT("can not to load FILE(0x{:016X})"), (uintptr_t) pFile));
	}
	
	void FImageData::Reset()
	{
		stbi_image_free(data);
		this->data = nullptr;
		this->width = 0;
		this->height = 0;
		this->n = 0;
	}
	
	FImageData::FImageData(const TString &file, int32_t desiredChannels)
		: FImageData()
	{
		LoadFromFile(file, desiredChannels);
	}
	
	FImageData::FImageData(FILE *pFile, int32_t desiredChannels)
		: FImageData()
	{
		LoadFromFile(pFile, desiredChannels);
	}
	
	
} // GenesisCube