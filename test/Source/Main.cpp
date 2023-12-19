//
// Created by admin on 2023/12/19.
//
#include <GenesisCubeEngine/Core/Core.h>

using namespace std;
using namespace GenesisCubeEngine;

namespace GenesisCubeEngineProgram
{
    
    void start()
    {
        
        MessageBox(NULL, Core::build_type, TEXT("Test1"), MB_OK);
        
    }
    
    void end()
    {
        
        MessageBox(NULL, Core::build_type, TEXT("Test2"), MB_OK);
        
    }
    
}


