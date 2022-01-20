//
//  IndexBufferObject.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef IndexBufferObject_hpp
#define IndexBufferObject_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <vector>

class IndexBufferObject {
public:
    IndexBufferObject(GLenum primitiveType, std::vector<unsigned int> data);
    ~IndexBufferObject();
    void Init();
    void Bind();
    void UnBind();
    void Draw();
private:
    unsigned int _mBO = 0;
    std::vector<unsigned int> _mData;
    GLenum _mPrimitiveType;
};

#endif /* IndexBufferObject_hpp */
