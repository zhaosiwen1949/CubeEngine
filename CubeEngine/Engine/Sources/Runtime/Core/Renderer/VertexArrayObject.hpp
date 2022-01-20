//
//  VertexArrayObject.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/26.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef VertexArrayObject_hpp
#define VertexArrayObject_hpp

#include <stdio.h>
#include <vector>
#include "VertexData.hpp"
#include "VertexBufferObject.hpp"
#include "IndexBufferObject.hpp"

class VertexArrayObject {
public:
    ~VertexArrayObject();
    void SetVBO(GLenum primitiveType, std::vector<VertexData> data);
    void SetIBO(GLenum primitiveType, std::vector<unsigned int> data);
    void Init();
    void Bind();
    void UnBind();
    void Draw();
private:
    unsigned int _mAO;
    VertexBufferObject* _mVBO = nullptr;
    IndexBufferObject* _mIBO = nullptr;
    bool _mbIsInitiated = false;
};


#endif /* VertexArrayObject_hpp */
