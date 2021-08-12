//
//  GlfwApplication.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/12.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "GlfwApplication.hpp"

GlfwApplication* GlfwApplication::_mApp = nullptr;

GlfwApplication* GlfwApplication::GetApp() noexcept {
    if(_mApp == nullptr) {
        _mApp = new GlfwApplication();
    }
    return _mApp;
}

int GlfwApplication::Initialize() noexcept {
    // 执行父类的初始化
    int flag = Application::Initialize();
    if(flag != 0){
        return flag;
    }
    
    // 初始化窗口参数
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    #endif
    
    mWindow = glfwCreateWindow(mWidth, mHeight, "Cube Engine", nullptr, nullptr);
    if(mWindow == nullptr){
        printf("窗口创建失败");
        // 结束窗口
        Finalize();
        return 1;
    }
    
    // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(mWindow);
    // 对窗口注册一个回调函数，每当窗口改变大小，GLFW会调用这个函数并填充相应的参数供你处理
    glfwSetFramebufferSizeCallback(mWindow, &GlfwApplication::FramebufferSizeCallback);
    // 对窗口注册一个回调函数，每当鼠标移动时，GLFW会调用这个函数，获取当前鼠标的位置，从而改变摄像机的朝向
//    glfwSetCursorPosCallback(mWindow, mouse_callback);
    // 对窗口注册一个回调函数，每当鼠标滚轮滑动时，GLFW会调用这个函数，获取滚动大小，从而改变视角大小，模拟缩放效果
//    glfwSetScrollCallback(mWindow, scroll_callback);
    // 初始化GLAD用来管理OpenGL的函数指针
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("GLAD初始化失败");
        return 1;
    }
    
    return 0;
};

void GlfwApplication::Render() noexcept {
    // 检查是否需要退出循环
    if(glfwWindowShouldClose(mWindow)) {
        Quit();
        return;
    }
    
    // 处理窗口的输入
    ProcessInput();
    
    // 调用 World 的渲染方法
    Application::Render();
    
    // 收尾工作
    PostHandle();
    
    return;
}

void GlfwApplication::Finalize() noexcept {
    glfwTerminate();
    Application::Finalize();
}

void GlfwApplication::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glad_glViewport(0, 0, width, height);
}

void GlfwApplication::ProcessInput() const {
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(mWindow, true);
    }
}

void GlfwApplication::PostHandle() const {
    // 检查调用事件，并交换缓存
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
}
