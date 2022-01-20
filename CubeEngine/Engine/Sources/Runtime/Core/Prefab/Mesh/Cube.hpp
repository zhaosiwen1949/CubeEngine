//
//  Cube.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/19.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include "../../Renderer/VertexArrayObject.hpp"

class Cube {
public:
    // TO DO: 这里的指针建议改成 shared_ptr，防止内存泄漏
    VertexArrayObject* mVAO;
public:
    static Cube* getCube();
    static Cube* _mCube;
};

#endif /* Cube_hpp */
