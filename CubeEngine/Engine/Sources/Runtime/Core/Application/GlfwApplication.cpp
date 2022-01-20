//
//  GlfwApplication.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/12.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "GlfwApplication.hpp"
#include <memory>
#include "../../Utils/Camera.hpp"
#include "../Object/Components/CameraComponent.hpp"

GlfwApplication* GlfwApplication::_mApp = nullptr;

bool GlfwApplication::_firstMouse = true;
float GlfwApplication::_lastX = Camera::SCR_WIDTH;
float GlfwApplication::_lastY = Camera::SCR_WIDTH;

GlfwApplication* GlfwApplication::GetApp() noexcept {
    if(_mApp == nullptr) {
        _mApp = new GlfwApplication();
    }
    return _mApp;
}

int GlfwApplication::Initialize() noexcept {
    // 初始化窗口参数
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    #endif
    
    _mWindow = glfwCreateWindow(Camera::SCR_WIDTH, Camera::SCR_HEIGHT, "Cube Engine", nullptr, nullptr);
    if(_mWindow == nullptr){
        printf("窗口创建失败");
        // 结束窗口
        Finalize();
        return 1;
    }
    
    // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(_mWindow);
    // 对窗口注册一个回调函数，每当窗口改变大小，GLFW会调用这个函数并填充相应的参数供你处理
    glfwSetFramebufferSizeCallback(_mWindow, &GlfwApplication::_FramebufferSizeCallback);
    // 对窗口注册一个回调函数，每当鼠标移动时，GLFW会调用这个函数，获取当前鼠标的位置，从而改变摄像机的朝向
    glfwSetCursorPosCallback(_mWindow, &GlfwApplication::_MouseCallback);
    // 对窗口注册一个回调函数，每当鼠标滚轮滑动时，GLFW会调用这个函数，获取滚动大小，从而改变视角大小，模拟缩放效果
    glfwSetScrollCallback(_mWindow, &GlfwApplication::_ScrollCallback);
    // 初始化GLAD用来管理OpenGL的函数指针
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("GLAD初始化失败");
        return 1;
    }
    
    // 执行父类的初始化
    // 注意：这里需要把父类初始化放在最后，是因为依赖窗口程序配置的 OpenGL 环境
    int flag = Application::Initialize();
    if(flag != 0){
        return flag;
    }
    
    return 0;
};

void GlfwApplication::Render() noexcept {
    // 检查是否需要退出循环
    if(glfwWindowShouldClose(_mWindow)) {
        Quit();
        return;
    }
    
    // 更新循环时间
    float currentTime = glfwGetTime();
    _deltaTime = currentTime - _lastTime;
    _lastTime = currentTime;
    
    // 处理窗口的输入
    _ProcessInput();
    
    // 调用 World 的渲染方法
    Application::Render();
    
    // 交换 Buffer
    _SwapBuffers();
    
    return;
}

void GlfwApplication::Finalize() noexcept {
    glfwTerminate();
    Application::Finalize();
}

void GlfwApplication::_FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glad_glViewport(0, 0, width, height);
}

void GlfwApplication::_MouseCallback(GLFWwindow *window, double xpos, double ypos) {
    std::shared_ptr<CameraComponent> camComp = _mApp->GetWorld()->GetCameraSystem()->FindComponent(CameraComponent::MAIN)[0];
    if(camComp != nullptr) {
        if(_firstMouse) {
            _lastX = xpos;
            _lastY = ypos;
            _firstMouse = false;
        }
        
        float xoffset = xpos - _lastX;
        float yoffset = _lastY - ypos;
        
        _lastX = xpos;
        _lastY = ypos;
        
        camComp->ProcessMouseMovement(xoffset, yoffset);
    }
}

void GlfwApplication::_ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    std::shared_ptr<CameraComponent> camComp = _mApp->GetWorld()->GetCameraSystem()->FindComponent(CameraComponent::MAIN)[0];
    if(camComp != nullptr) {
        camComp->ProcessMouseScroll(yoffset);
    }
}

void GlfwApplication::_ProcessInput() const {
    if(glfwGetKey(_mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(_mWindow, true);
    }
    
    std::shared_ptr<CameraComponent> camComp = GetWorld()->GetCameraSystem()->FindComponent(CameraComponent::MAIN)[0];
    if(camComp != nullptr) {
        if (glfwGetKey(_mWindow, GLFW_KEY_W) == GLFW_PRESS){
            camComp->ProcessKeyboard(Camera::FORWARD, _deltaTime);
        }else if (glfwGetKey(_mWindow, GLFW_KEY_S) == GLFW_PRESS){
            camComp->ProcessKeyboard(Camera::BACKWARD, _deltaTime);
        }else if (glfwGetKey(_mWindow, GLFW_KEY_A) == GLFW_PRESS){
            camComp->ProcessKeyboard(Camera::LEFT, _deltaTime);
        }else if (glfwGetKey(_mWindow, GLFW_KEY_D) == GLFW_PRESS){
            camComp->ProcessKeyboard(Camera::RIGHT, _deltaTime);
        }else if (glfwGetKey(_mWindow, GLFW_KEY_Q) == GLFW_PRESS){
            camComp->ProcessKeyRollMovement(-_deltaTime, 0);
        }else if (glfwGetKey(_mWindow, GLFW_KEY_E) == GLFW_PRESS){
            camComp->ProcessKeyRollMovement(_deltaTime, 0);
        }else if (glfwGetKey(_mWindow, GLFW_KEY_R) == GLFW_PRESS){
            camComp->ProcessKeyRollMovement(0, _deltaTime);
        }else if (glfwGetKey(_mWindow, GLFW_KEY_F) == GLFW_PRESS){
            camComp->ProcessKeyRollMovement(0, -_deltaTime);
        }
    }
}

void GlfwApplication::_SwapBuffers() const {
    // 检查调用事件，并交换缓存
    glfwPollEvents();
    glfwSwapBuffers(_mWindow);
}
