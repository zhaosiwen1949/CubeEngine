//
//  Application.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/11.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "Application.hpp"

int Application::Initialize() noexcept {
    // 初始化 World 对象，管理 ECS 系统
    _mWorld = new World(this);
    int flag = _mWorld->Initialize();
    
    return flag;
}

void Application::Render() noexcept{
    _mWorld->Render();
}

void Application::Run() noexcept{
    while (!IsQuit())
    {
        Render();
    }
}

void Application::Finalize() noexcept {
    _mWorld->Finalize();
}

bool Application::IsQuit() noexcept {
    return _mQuit;
}

void Application::Quit() noexcept {
    _mQuit = true;
}


