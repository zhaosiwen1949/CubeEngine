//
//  MaterialProperty.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef MaterialProperty_hpp
#define MaterialProperty_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "Texture2D.hpp"

enum UniformType {
    kUniformTypeVec4 = 1,
    kUniformTypeVec3,
    kUniformTypeMat4,
    kUniformTypeFloat,
    kUniformTypeTexture,
};

class MaterialProperty {
public:
    MaterialProperty(std::string name, UniformType type): _mName(name), _mType(type) {};
    virtual ~MaterialProperty() = default;
    inline std::string GetName() const {
        return _mName;
    };
    inline bool isType(UniformType type) const {
        return type == _mType;
    }
private:
    std::string _mName;
    UniformType _mType;
};

class UniformVector4Property: public MaterialProperty {
public:
    UniformVector4Property(std::string name, glm::vec4 value): MaterialProperty(name, kUniformTypeVec4), _mValue(value) {};
    ~UniformVector4Property() override {};
    inline glm::vec4 GetValue() const {
        return _mValue;
    }
    // TO DO: 这里的设置值可以改成友元函数
    inline void SetValue(float x, float y, float z, float w) {
        _mValue.x = x;
        _mValue.y = y;
        _mValue.z = z;
        _mValue.w = w;
    }
    inline void SetValue(glm::vec4 value) {
        _mValue = value;
    }
private:
    glm::vec4 _mValue;
};

class UniformVector3Property: public MaterialProperty {
public:
    UniformVector3Property(std::string name, glm::vec3 value): MaterialProperty(name, kUniformTypeVec3), _mValue(value) {};
    ~UniformVector3Property() override {};
    inline glm::vec3 GetValue() const {
        return _mValue;
    }
    // TO DO: 这里的设置值可以改成友元函数
    inline void SetValue(float x, float y, float z) {
        _mValue.x = x;
        _mValue.y = y;
        _mValue.z = z;
    }
    inline void SetValue(glm::vec3 value) {
        _mValue = value;
    }
private:
    glm::vec3 _mValue;
};

class UniformMatrix4Property: public MaterialProperty {
public:
    UniformMatrix4Property(std::string name, glm::mat4 value): MaterialProperty(name, kUniformTypeMat4), _mValue(value) {};
    ~UniformMatrix4Property() override {};
    inline glm::mat4 GetValue() const {
        return _mValue;
    }
    // TO DO: 这里的设置值可以改成友元函数
    inline void SetValue(glm::mat4 value) {
        _mValue = value;
    }
private:
    glm::mat4 _mValue;
};

class UniformFloatProperty: public MaterialProperty {
public:
    UniformFloatProperty(std::string name, float value): MaterialProperty(name, kUniformTypeFloat), _mValue(value) {};
    ~UniformFloatProperty() override {};
    inline float GetValue() const {
        return _mValue;
    }
    // TO DO: 这里的设置值可以改成友元函数
    inline void SetValue(float value) {
        _mValue = value;
    }
private:
    float _mValue;
};

class UniformTextureProperty: public MaterialProperty {
public:
    UniformTextureProperty(std::string name): MaterialProperty(name, kUniformTypeTexture) {};
    ~UniformTextureProperty() override {};
    inline GLint GetSlot() const {
        return _mSlot;
    }
    // TO DO: 这里的设置值可以改成友元函数
    inline void SetSlot(GLint slot) {
        _mSlot = slot;
    }
    inline std::shared_ptr<Texture2D> GetTexture() const {
        return _mTexture;
    }
    // TO DO: 这里的设置值可以改成友元函数
    inline void SetTexture(std::shared_ptr<Texture2D> texture) {
        _mTexture = texture;
    }
private:
    GLint _mSlot = -1;
    std::shared_ptr<Texture2D> _mTexture = nullptr;
};

#endif /* MaterialProperty_hpp */
