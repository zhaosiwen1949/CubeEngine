//
//  Triangle.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/25.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include "../../Renderer/VertexArrayObject.hpp"


class Triangle {
public:
    // TO DO: 这里的指针建议改成 shared_ptr，防止内存泄漏
    VertexArrayObject* mVAO;
public:
    static Triangle* getTriangle();
    static Triangle* _mTriangle;
};

#endif /* Triangle_hpp */
