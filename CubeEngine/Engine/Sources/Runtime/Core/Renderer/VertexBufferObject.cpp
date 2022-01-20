//
//  VertexBufferObject.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "VertexBufferObject.hpp"
#include "RenderState.hpp"

VertexBufferObject::VertexBufferObject(GLenum primitiveType, std::vector<VertexData> data): _mPrimitiveType(primitiveType), _mData(data) {}

VertexBufferObject::~VertexBufferObject() {
    if(_mBO != 0) {
        glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
        glad_glDeleteBuffers(1, &_mBO);
    }
}

void VertexBufferObject::Init() {
    if(_mBO != 0) {
        glad_glDeleteBuffers(1, &_mBO);
    }
    glad_glGenBuffers(1, &_mBO);
    glad_glBindBuffer(GL_ARRAY_BUFFER, _mBO);
    glad_glBufferData(GL_ARRAY_BUFFER, (unsigned int)_mData.size() * sizeof(VertexData), &_mData[0], GL_STATIC_DRAW);
    glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Enable() {
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
    GlobalRenderState::EnableAttribute(0, true);
    glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, normal));
    GlobalRenderState::EnableAttribute(1, true);
    glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, texcoord0));
    GlobalRenderState::EnableAttribute(2, true);
}

void VertexBufferObject::Bind() {
    glad_glBindBuffer(GL_ARRAY_BUFFER, _mBO);
}

void VertexBufferObject::UnBind() {
    glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Draw() {
    glad_glDrawArrays(_mPrimitiveType, 0, (unsigned int)_mData.size());
}
