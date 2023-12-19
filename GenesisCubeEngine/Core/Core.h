//
// Created by admin on 2023/12/19.
//

#pragma once
#include "GenesisCubeEngine.h"

namespace GenesisCubeEngine
{
    //
    // 核心类
    //
    class Core
    {
    public:
        
        //
        // 测试
        //
        static void TestGenesisCubeEngine();
        
    public:
        
        //
        // 项目名称
        //
        static TCHAR name[];
        
        //
        // 版本字符串
        // 样式：大版本号 ## . ## 小版本号 ## - ## 版本类型
        // 例如：1.0-alpha
        // alpha - Debug测试版
        // beta - Release测试版
        // release - Release正式版
        //
        static TCHAR version_string[];
        
        //
        // 编译时间
        //
        static TCHAR build_time[];
        
        //
        // 编译类型
        //
        static TCHAR build_type[];
        
        //
        // 版本代码
        // 样式：0x ## 大版本号 ## 小版本号
        // 例如：0x0100
        //
        static int version_code;
        
    };
    
   
    
} // GenesisCubeEngine

namespace GenesisCubeEngineProgram
{
    //
    // 程序开始时
    //
    void start();
    
    //
    // 程序结束时
    //
    void end();
}
