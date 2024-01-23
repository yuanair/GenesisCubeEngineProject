//
// Created by admin on 2024/1/23.
//

#pragma once

#include "Header.h"
#include "FCore.h"
#include "GenesisCubeBase/Exception/EException.h"
#include "GenesisCubeBase/Core/Debug.h"


int WINAPI
#ifdef UNICODE
wWinMain
#else
WinMain
#endif
	(HINSTANCE, HINSTANCE, LPTSTR, int)
{
#ifdef _DEBUG
	return main();
#else
	try
	{
		return main();
	}
	catch (const GenesisCube::EException &ex)
	{
		GenesisCube::FLogger::MessageBoxFromException(ex);
		return 0;
	}
	catch (const std::exception &ex)
	{
		GenesisCube::FLogger::MessageBoxFromException(ex);
		return 0;
	}
#endif
}
