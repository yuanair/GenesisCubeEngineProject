//
// Created by admin on 2023/12/19.
//

#pragma once

#include <windows.h>
#include <windowsx.h>

#include <typeinfo>
#include <fstream>
#include <format>
#include <string>
#include <vector>
#include <list>
#include <map>


#if defined(_DEBUG) || defined(DEBUG) || defined(GenesisCubeEditor)

#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <crtdbg.h>
#include <dbghelp.h>

#pragma comment(lib, "DbgHelp.lib")

#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#endif
