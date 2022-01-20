//
//  Shader.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <glad/glad.h>

// TO DO: Shader 可以做缓存，返回 shared_ptr
class Shader {
public:
    static std::shared_ptr<Shader> GetShader(std::string vsPath, std::string fsPath);
public:
    struct UniformInfo {
        GLenum type;
        GLuint location;
        std::string name;
    };
    ~Shader();
    // TO DO: Init、Bind 函数可以进一步做成 Material 友元函数
    void Init(std::string vsPath, std::string fsPath);
    void BindProgram();
    inline std::vector<UniformInfo> GetUniformInfoList() const {
        return _mUniformInfoList;
    };
private:
    static std::unordered_map<std::string, std::weak_ptr<Shader>> _mShaderMap;
private:
    std::vector<UniformInfo> _mUniformInfoList;
    
    // Program
    GLuint _mProgram;
    void LoadShader(std::string vsPath, std::string fsPath);
    void InitUniformInfoList();
};

#endif /* Shader_hpp */
