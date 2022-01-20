//
//  IndexBufferObject.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "IndexBufferObject.hpp"
#include <glm/glm.hpp>

IndexBufferObject::IndexBufferObject(GLenum primitiveType, std::vector<unsigned int> data): _mPrimitiveType(primitiveType), _mData(data) {}

IndexBufferObject::~IndexBufferObject() {
    if(_mBO != 0) {
        glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
        glad_glDeleteBuffers(1, &_mBO);
    }
}

void IndexBufferObject::Init() {
    if(_mBO != 0) {
        glad_glDeleteBuffers(1, &_mBO);
    }
    glad_glGenBuffers(1, &_mBO);
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mBO);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int)_mData.size() * sizeof(unsigned int), &_mData[0], GL_STATIC_DRAW);
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferObject::Bind() {
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mBO);
}

void IndexBufferObject::UnBind() {
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferObject::Draw() {
    glad_glDrawElements(_mPrimitiveType, (unsigned int)_mData.size(), GL_UNSIGNED_INT, 0);
}
