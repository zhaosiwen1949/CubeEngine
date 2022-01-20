//
//  Material.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "Material.hpp"

Material::~Material() {
    // 销毁 RenderState
    delete mRenderState;
    mRenderState = nullptr;
    // 销毁 UniformBinder
    UniformBinder* currentUniformBinder = _mUniformBinder;
    while(currentUniformBinder != nullptr) {
        UniformBinder* nextUniformBinder = currentUniformBinder->Next<UniformBinder>();
        delete currentUniformBinder;
        currentUniformBinder = nextUniformBinder;
    }
}

void Material::Init(std::string vsPath, std::string fsPath) {
    // 初始化 Shader
    _mShader = Shader::GetShader(vsPath, fsPath);
    
    // 拷贝 Shader 上的 UniformBinder，用来初始化属性列表
    std::vector<Shader::UniformInfo> uniformInfoList = _mShader->GetUniformInfoList();
    
    // 遍历容器，创建 MaterialProperty 和 UniformBinder
    // TO DO: 去掉 MaterialProperty 和 UniformBinder 的 Clone 方法
    UniformBinder* binder = nullptr;
    std::shared_ptr<MaterialProperty> materialProperty = nullptr;
    for(auto& uniformInfo : uniformInfoList) {
        if(uniformInfo.type == GL_FLOAT_VEC4) {
            materialProperty = std::make_shared<UniformVector4Property>(uniformInfo.name, glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f});
            binder = new UniformBinder(uniformInfo.location, UniformBinder::UpdateVec4, materialProperty);
        } else if (uniformInfo.type == GL_FLOAT_VEC3) {
            materialProperty = std::make_shared<UniformVector3Property>(uniformInfo.name, glm::vec3 {0.0f, 0.0f, 0.0f});
            binder = new UniformBinder(uniformInfo.location, UniformBinder::UpdateVec3, materialProperty);
        } else if (uniformInfo.type == GL_FLOAT_MAT4) {
            materialProperty = std::make_shared<UniformMatrix4Property>(uniformInfo.name, glm::mat4 {1.0f});
            binder = new UniformBinder(uniformInfo.location, UniformBinder::UpdateMat4, materialProperty);
        } else if (uniformInfo.type == GL_FLOAT) {
            materialProperty = std::make_shared<UniformFloatProperty>(uniformInfo.name, 1.0f);
            binder = new UniformBinder(uniformInfo.location, UniformBinder::UpdateFloat, materialProperty);
        } else if (uniformInfo.type == GL_SAMPLER_2D) {
            materialProperty = std::make_shared<UniformTextureProperty>(uniformInfo.name);
            binder = new UniformBinder(uniformInfo.location, UniformBinder::UpdateTexture, materialProperty);
        } else {
            printf("Uniform 属性：%s 不存在对应的 MaterialProperty\n", uniformInfo.name.c_str());
        }
        if(_mUniformBinder == nullptr) {
            _mUniformBinder = binder;
        } else {
            _mUniformBinder->PushBack(binder);
        }
        _mMaterialPropertyMap.insert({materialProperty->GetName(), materialProperty});
        
    }
    
    // 初始化 RenderState
    mRenderState = new RenderState;
}

void Material::Bind() {
    // 设置 RenderState
    mRenderState->Bind();
    
    // 设置 Uniform 常量属性
    _mShader->BindProgram();
    UniformBinder* currentUniformBinder = _mUniformBinder;
    int nTextureSlot = 0;
    while(currentUniformBinder != nullptr) {
        if(currentUniformBinder->GetMaterialProperty()->isType(kUniformTypeTexture)) {
            // 贴图属性，设置插槽
            std::shared_ptr<UniformTextureProperty> property = std::dynamic_pointer_cast<UniformTextureProperty>(currentUniformBinder->GetMaterialProperty());
            property->SetSlot(nTextureSlot);
            nTextureSlot += 1;
        }
        currentUniformBinder->Bind();
        currentUniformBinder = currentUniformBinder->Next<UniformBinder>();
    }
}

void Material::SetVec4Property(std::string name, float x, float y, float z, float w) {
    const auto& iter = _mMaterialPropertyMap.find(name);
    if(iter != _mMaterialPropertyMap.end()) {
        if(iter->second->isType(kUniformTypeVec4)) {
            std::shared_ptr<UniformVector4Property> property = std::dynamic_pointer_cast<UniformVector4Property>(iter->second);
            property->SetValue(x, y, z, w);
        } else {
            printf("属性 %s 不是 vec4 类型，无法设置", name.c_str());
        }
    } else {
//        printf("未找到属性 %s", name.c_str());
    }
}

void Material::SetVec4Property(std::string name, glm::vec4 value) {
    const auto& iter = _mMaterialPropertyMap.find(name);
    if(iter != _mMaterialPropertyMap.end()) {
        if(iter->second->isType(kUniformTypeVec4)) {
            std::shared_ptr<UniformVector4Property> property = std::dynamic_pointer_cast<UniformVector4Property>(iter->second);
            property->SetValue(value);
        } else {
            printf("属性 %s 不是 vec4 类型，无法设置", name.c_str());
        }
    } else {
//        printf("未找到属性 %s", name.c_str());
    }
}

void Material::SetVec3Property(std::string name, float x, float y, float z) {
    const auto& iter = _mMaterialPropertyMap.find(name);
    if(iter != _mMaterialPropertyMap.end()) {
        if(iter->second->isType(kUniformTypeVec3)) {
            std::shared_ptr<UniformVector3Property> property = std::dynamic_pointer_cast<UniformVector3Property>(iter->second);
            property->SetValue(x, y, z);
        } else {
            printf("属性 %s 不是 vec3 类型，无法设置", name.c_str());
        }
    } else {
//        printf("未找到属性 %s", name.c_str());
    }
}

void Material::SetVec3Property(std::string name, glm::vec3 value) {
    const auto& iter = _mMaterialPropertyMap.find(name);
    if(iter != _mMaterialPropertyMap.end()) {
        if(iter->second->isType(kUniformTypeVec3)) {
            std::shared_ptr<UniformVector3Property> property = std::dynamic_pointer_cast<UniformVector3Property>(iter->second);
            property->SetValue(value);
        } else {
            printf("属性 %s 不是 vec3 类型，无法设置", name.c_str());
        }
    } else {
//        printf("未找到属性 %s", name.c_str());
    }
}

void Material::SetMat4Property(std::string name, glm::mat4 value) {
    const auto& iter = _mMaterialPropertyMap.find(name);
    if(iter != _mMaterialPropertyMap.end()) {
        if(iter->second->isType(kUniformTypeMat4)) {
            std::shared_ptr<UniformMatrix4Property> property = std::dynamic_pointer_cast<UniformMatrix4Property>(iter->second);
            property->SetValue(value);
        } else {
            printf("属性 %s 不是 vec4 类型，无法设置", name.c_str());
        }
    } else {
//        printf("未找到属性 %s", name.c_str());
    }
}

void Material::SetFloatProperty(std::string name, float value) {
    const auto& iter = _mMaterialPropertyMap.find(name);
    if(iter != _mMaterialPropertyMap.end()) {
        if(iter->second->isType(kUniformTypeFloat)) {
            std::shared_ptr<UniformFloatProperty> property = std::dynamic_pointer_cast<UniformFloatProperty>(iter->second);
            property->SetValue(value);
        } else {
            printf("属性 %s 不是 float 类型，无法设置", name.c_str());
        }
    } else {
//        printf("未找到属性 %s", name.c_str());
    }
}

void Material::SetTextureProperty(std::string name, std::shared_ptr<Texture2D> texture) {
    const auto& iter = _mMaterialPropertyMap.find(name);
    if(iter != _mMaterialPropertyMap.end()) {
        if(iter->second->isType(kUniformTypeTexture)) {
            std::shared_ptr<UniformTextureProperty> property = std::dynamic_pointer_cast<UniformTextureProperty>(iter->second);
            property->SetTexture(texture);
        } else {
            printf("属性 %s 不是 float 类型，无法设置", name.c_str());
        }
    } else {
//        printf("未找到属性 %s", name.c_str());
    }
}
