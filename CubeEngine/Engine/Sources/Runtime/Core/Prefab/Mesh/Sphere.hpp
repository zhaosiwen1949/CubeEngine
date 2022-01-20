//
//  Sphere.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/19.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include "../../Renderer/VertexArrayObject.hpp"

class Sphere {
public:
    // TO DO: 这里的指针建议改成 shared_ptr，防止内存泄漏
    VertexArrayObject* mVAO;
    static void SetVAO1();
    static void SetVAO2();
public:
    static Sphere* getSphere();
    static Sphere* _mSphere;
};


#endif /* Sphere_hpp */
