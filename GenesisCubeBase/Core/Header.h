//
// Created by admin on 2023/12/19.
//

#pragma once

#include <msctf.h>
#include <wrl.h>

#include <typeinfo>
#include <fstream>
#include <format>
#include <string>
#include <vector>
#include <list>
#include <map>

#pragma comment(lib, "Imm32.lib")

#if defined(_DEBUG) || defined(DEBUG)

#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <crtdbg.h>
#include <dbghelp.h>

#pragma comment(lib, "DbgHelp.lib")

#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#endif
