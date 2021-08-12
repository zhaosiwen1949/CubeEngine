//
//  main.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/11.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "../Runtime/Core/Application/GlfwApplication.hpp"


int main(int argc, const char * argv[]) {
    // 获取 Application
    GlfwApplication* app = GlfwApplication::GetApp();
    
    // 初始化 Application
    app->Initialize();
    
    // 加载场景
    
    // 开始渲染循环
    app->Run();
    
    // 结束应用，释放资源
    app->Finalize();
    
    return 0;
}
