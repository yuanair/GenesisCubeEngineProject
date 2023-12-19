//
// Created by admin on 2023/12/19.
//

#pragma once

#include <windows.h>
#include <windowsx.h>

#include <typeinfo>
#include <string>
#include <vector>
#include <map>


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <crtdbg.h>

#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#endif
