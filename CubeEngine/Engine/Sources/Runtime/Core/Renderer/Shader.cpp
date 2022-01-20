//
//  Shader.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include "VertexData.hpp"

std::unordered_map<std::string, std::weak_ptr<Shader>> Shader::_mShaderMap;

std::shared_ptr<Shader> Shader::GetShader(std::string vsPath, std::string fsPath) {
    // 查找 Shader 缓存
    std::shared_ptr<Shader> shader;
    std::string key = vsPath + fsPath;
    const auto& iter = _mShaderMap.find(key);
    if(iter != _mShaderMap.cend() && (shader = iter->second.lock())) {
        return shader;
    }
    // 没有在缓存中查找到，需要新建
    shader = std::make_shared<Shader>();
    shader->Init(vsPath, fsPath);
    // 加入到缓存中
    _mShaderMap.insert({key, shader});
    return shader;
};

Shader::~Shader() {
    glad_glDeleteProgram(_mProgram);
}

void Shader::Init(std::string vsPath, std::string fsPath) {
    // 加载 vs、fs 程序
    LoadShader(vsPath, fsPath);
    
    // 初始化 UniformBinder
    InitUniformInfoList();
}

void Shader::LoadShader(std::string vsPath, std::string fsPath) {
    std::string vShaderSource, fShaderSource;
    // 1. 从文件路径中获取顶点/片段着色器源码
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // 打开文件
        vShaderFile.open(vsPath);
        fShaderFile.open(fsPath);
        
        // 读取文件内容到数据流
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        // 关闭文件
        vShaderFile.close();
        fShaderFile.close();
        
        // 转换数据流到字符串
        vShaderSource = vShaderStream.str();
        fShaderSource = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        printf("Shader 文件加载错误\n");
    }
    
    const char* vShaderSourceC = vShaderSource.c_str();
    const char* fShaderSourceC = fShaderSource.c_str();
    
    // 2、编译着色器
    int successs;
    char infoLog[512];
    
    // 编译顶点着色器
    unsigned int vertex = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertex, 1, &vShaderSourceC, nullptr);
    glad_glCompileShader(vertex);
    glad_glGetShaderiv(vertex, GL_COMPILE_STATUS, &successs);
    if(!successs){
        glad_glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        printf("顶点着色器编译错误:");
        printf(infoLog);
        printf("\n");
    }
    
    // 编译片元着色器
    unsigned int fragment = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(fragment, 1, &fShaderSourceC, nullptr);
    glad_glCompileShader(fragment);
    glad_glGetShaderiv(fragment, GL_COMPILE_STATUS, &successs);
    if(!successs){
        glad_glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        printf("片元着色器编译错误:");
        printf(infoLog);
        printf("\n");
    }
    
    // 创建着色程序，并链接着色器
    _mProgram = glad_glCreateProgram();
    glad_glAttachShader(_mProgram, vertex);
    glad_glAttachShader(_mProgram, fragment);
    glad_glLinkProgram(_mProgram);
    glad_glGetProgramiv(_mProgram, GL_LINK_STATUS, &successs);
    if(!successs){
        glad_glGetProgramInfoLog(_mProgram, 512, nullptr, infoLog);
        printf("着色程序链接错误:");
        printf(infoLog);
        printf("\n");
    }
    
    // 删除 shader
    glad_glDeleteShader(vertex);
    glad_glDeleteShader(fragment);
}

void Shader::InitUniformInfoList() {
    GLint count; // Shader 中 顶点属性的数量

    GLint size; // 属性数组的长度，如果不是数组则为 1
    GLenum type; // 属性类型

    const GLsizei bufSize = 64; // 允许的名字的长度
    GLchar name[bufSize]; // 名字的内容
    GLsizei length; // 名字真实的长度
    
    // 1、获取 Attribute
    glad_glGetProgramiv(_mProgram, GL_ACTIVE_UNIFORMS, &count);
    printf("获取到常量属性，共 %d 个\n", count);
    
    // 2、遍历创建 Uniform Binder 链
    for(GLuint i = 0; i < count; i++) {
        glad_glGetActiveUniform(_mProgram, i, bufSize, &length, &size, &type, name);
        if(size > 1) {
            for(unsigned int k = 0; k < 4; ++k) {
                std::string tname = name;
                tname.replace(tname.find("["), tname.rfind("]"), "[" + std::to_string(k) + "]");
                printf("第 %d 个常量属性是 %x 类型【数组】，长度是 %d，名称是 %s\n", i, type, size, tname.c_str());
                GLint location = glad_glGetUniformLocation(_mProgram, tname.c_str());
                _mUniformInfoList.push_back(UniformInfo { type, (GLuint)location, tname });
            }
        } else {
            printf("第 %d 个常量属性是 %x 类型，长度是 %d，名称是 %s\n", i, type, size, name);
            GLint location = glad_glGetUniformLocation(_mProgram, name);
            _mUniformInfoList.push_back(UniformInfo { type, (GLuint)location, name });
        }
    }
}

void Shader::BindProgram() {
    glad_glUseProgram(_mProgram);
}
