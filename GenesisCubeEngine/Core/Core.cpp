//
// Created by admin on 2023/12/19.
//

#include "Core.h"

namespace GenesisCubeEngine
{

    TCHAR Core::name[] = TEXT("Genesis Cube Engine");
    
    TCHAR Core::version_string[] = TEXT("0.1-alpha");
    
    TCHAR Core::build_time[] = TEXT(__DATE__);
    
    int Core::version_code = 1;


#if defined(GenesisCubeEditorDebug)
    TCHAR Core::build_type[] = TEXT("Editor Debug");
#elif defined(GenesisCubeEditorRelease)
    TCHAR Core::build_type[] = TEXT("Editor Release");
#elif defined(GenesisCubeGameDebug)
    TCHAR Core::build_type[] = TEXT("Game Debug");
#elif defined(GenesisCubeGameRelease)
    TCHAR Core::build_type[] = TEXT("Game Release");
#else
    TCHAR Core::build_type[] = TEXT("Error Error");
#endif
    
    void Core::TestGenesisCubeEngine()
    {
        MessageBox(NULL, build_type, TEXT("GCE编译类型"), MB_OK);
        MessageBox(NULL, TEXT("<Test field测试字段>"), TEXT("GCE测试"), MB_OK);
    }
    
} // GenesisCubeEngine

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    GenesisCubeEngine::Core::TestGenesisCubeEngine();
    GenesisCubeEngineProgram::start();
    
    GenesisCubeEngineProgram::end();
    
    return 0;
}
