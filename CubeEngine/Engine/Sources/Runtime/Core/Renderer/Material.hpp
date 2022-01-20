//
//  Material.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <glm/glm.hpp>
#include "Texture2D.hpp"
#include "Shader.hpp"
#include "UniformBinder.hpp"
#include "MaterialProperty.hpp"
#include "RenderState.hpp"

class Material {
public:
    // RenderState
    // TO DO: 注意 RenderState 的内存回收
    RenderState* mRenderState;
    ~Material();
    void Init(std::string vsPath, std::string fsPath);
    void Bind();
    // 设置 MaterialProperty
    void SetVec4Property(std::string name, float x, float y, float z, float w);
    void SetVec4Property(std::string name, glm::vec4 value);
    void SetVec3Property(std::string name, float x, float y, float z);
    void SetVec3Property(std::string name, glm::vec3 value);
    void SetMat4Property(std::string name, glm::mat4 value);
    void SetFloatProperty(std::string name, float value);
    void SetTextureProperty(std::string name, std::shared_ptr<Texture2D> texture);
private:
    // Shader
    // Shader 的作用：
    // 1、获取 Program；
    // 2、获取 Uniform 数据；
    std::shared_ptr<Shader> _mShader;
    
    // MaterialProperty 集合
    // 根据属性名，查找属性值
    // TO DO: MaterialProperty 是否做成智能指针，注意内存回收
    std::unordered_map<std::string, std::shared_ptr<MaterialProperty>> _mMaterialPropertyMap;
    // TO DO: 注意链表移除的内存回收
    // UniformBinder
    UniformBinder* _mUniformBinder = nullptr;
    
    // RenderPass ?
};

#endif /* Material_hpp */
