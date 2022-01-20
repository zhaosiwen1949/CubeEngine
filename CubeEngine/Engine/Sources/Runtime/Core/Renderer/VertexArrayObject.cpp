//
//  VertexArrayObject.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/26.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "VertexArrayObject.hpp"

VertexArrayObject::~VertexArrayObject() {
    if(_mAO != 0) {
        glad_glBindVertexArray(0);
        glad_glDeleteVertexArrays(1, &_mAO);
    }
    
    if(_mVBO != nullptr) {
        delete _mVBO;
        _mVBO = nullptr;
    }
    
    if(_mIBO != nullptr) {
        delete _mIBO;
        _mIBO = nullptr;
    }
}

void VertexArrayObject::SetVBO(GLenum primitiveType, std::vector<VertexData> data) {
    _mVBO = new VertexBufferObject(primitiveType, data);
    _mVBO->Init();
};

void VertexArrayObject::SetIBO(GLenum primitiveType, std::vector<unsigned int> data) {
    _mIBO = new IndexBufferObject(primitiveType, data);
    _mIBO->Init();
};

void VertexArrayObject::Init() {
    if(!_mbIsInitiated) {
        // 创建 VAO
        glad_glGenVertexArrays(1, &_mAO);
        
        // 绑定 VAO
        glad_glBindVertexArray(_mAO);
        
        // 绑定 VBO，并提交顶点格式
        if(_mVBO != nullptr) {
            _mVBO->Bind();
            _mVBO->Enable();
        }
        
        // 绑定 IBO
        if(_mIBO != nullptr) {
            _mIBO->Bind();
        }
        
        // 解绑 VAO
        UnBind();
        
        // 解绑 VBO
        if(_mVBO != nullptr) {
            _mVBO->UnBind();
        }
        
        // 解绑 IBO
        if(_mIBO != nullptr) {
            _mIBO->UnBind();
        }
        
        // 配置初始化标志位
        _mbIsInitiated = true;
    }
}

void VertexArrayObject::Bind() {
    glad_glBindVertexArray(_mAO);
}

void VertexArrayObject::UnBind() {
    glad_glBindVertexArray(0);
}

void VertexArrayObject::Draw() {
    if(_mIBO == nullptr) {
        _mVBO->Draw();
    } else {
        _mIBO->Draw();
    }
}
