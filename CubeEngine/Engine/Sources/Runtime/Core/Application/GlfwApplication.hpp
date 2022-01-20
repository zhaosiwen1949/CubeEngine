//
//  GlfwApplication.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/12.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef GlfwApplication_hpp
#define GlfwApplication_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.hpp"

class GlfwApplication: public Application {
public:
    int Initialize() noexcept override;
    void Finalize() noexcept override;
    void Render() noexcept override;
    
    static GlfwApplication* GetApp() noexcept;
    
private:
    // 唯一 App 实例
    static GlfwApplication* _mApp;
    
    // 窗口参数
    GLFWwindow* _mWindow;
    
    // 记录每一帧更新的间隔时间
    float _deltaTime = 0.0f;
    float _lastTime = 0.0f;
    
    // 窗口回调参数
    static void _FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    // 鼠标移动回调参数
    static bool _firstMouse;
    static float _lastX;
    static float _lastY;
    static void _MouseCallback(GLFWwindow* window, double xpos, double ypos);
    // 鼠标滚动回调参数
    static void _ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    
    // 绑定按键
    void _ProcessInput() const;
    // 切换 Buffer
    void _SwapBuffers() const;
    
};

#endif /* GlfwApplication_hpp */
