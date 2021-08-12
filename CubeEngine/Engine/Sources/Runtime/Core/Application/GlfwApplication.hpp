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
    GLFWwindow* mWindow;
    int mWidth = 800;
    int mHeight = 600;
    
    // 窗口回调参数
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    
    // 绑定按键
    void ProcessInput() const;
    // 切换 Buffer
    void PostHandle() const;
    
};

#endif /* GlfwApplication_hpp */
