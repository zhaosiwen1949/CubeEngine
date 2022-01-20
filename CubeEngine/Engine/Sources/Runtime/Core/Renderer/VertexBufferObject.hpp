//
//  VertexBufferObject.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef VertexBufferObject_hpp
#define VertexBufferObject_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <vector>
#include "VertexData.hpp"

class VertexBufferObject {
public:
    VertexBufferObject(GLenum primitiveType, std::vector<VertexData> data);
    ~VertexBufferObject();
    void Init();
    void Enable();
    void Bind();
    void UnBind();
    void Draw();
private:
    unsigned int _mBO = 0;
    std::vector<VertexData> _mData;
    GLenum _mPrimitiveType;
};

#endif /* VertexBufferObject_hpp */
