//
// Created by admin on 2023/12/19.
//

#pragma once

#include <windows.h>
#include <windowsx.h>
#include <msctf.h>
#include <wrl.h>

#include <d3d11.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>

#include <DirectXMath.h>

#include <typeinfo>
#include <fstream>
#include <format>
#include <string>
#include <vector>
#include <list>
#include <map>

#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dWrite.lib")

#if defined(_DEBUG) || defined(DEBUG) || defined(GenesisCubeEditor)

#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <crtdbg.h>
#include <dbghelp.h>

#pragma comment(lib, "DbgHelp.lib")

#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#endif

