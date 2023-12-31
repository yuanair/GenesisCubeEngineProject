//
// Created by admin on 2023/12/27.
//

#include "FImageData.h"
#include "../DoNotInclude/stb_image.h"

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
	
	bool FImageData::LoadFromFile(const TString &file, int32_t desiredChannels)
	{
		Reset();
		FILE *pFile;
#ifdef UNICODE
		_wfopen_s
#else
			_fopen_s
#endif
			(&pFile, file.c_str(), TEXT("rb"));
		if (pFile == nullptr) return false;
		this->data = stbi_load_from_file(pFile, &this->width, &this->height, &this->n, desiredChannels);
		fclose(pFile);
		return this->data != nullptr;
	}
	
	bool FImageData::LoadFromFile(FILE *pFile, int32_t desiredChannels)
	{
		Reset();
		this->data = stbi_load_from_file(pFile, &this->width, &this->height, &this->n, desiredChannels);
		return this->data != nullptr;
	}
	
	void FImageData::Reset()
	{
		stbi_image_free(data);
		this->data = nullptr;
		this->width = 0;
		this->height = 0;
		this->n = 0;
	}
	
	
} // GenesisCube