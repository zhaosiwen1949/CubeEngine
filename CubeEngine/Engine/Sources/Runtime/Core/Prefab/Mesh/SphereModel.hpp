//
//  SphereModel.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/31.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef SphereModel_hpp
#define SphereModel_hpp

#include <stdio.h>
#include "../../Renderer/VertexArrayObject.hpp"

class SphereModel {
public:
    // TO DO: 这里的指针建议改成 shared_ptr，防止内存泄漏
    VertexArrayObject* mVAO;
public:
    static SphereModel* getSphereModel();
    static SphereModel* _mSphereModel;
};

#endif /* SphereModel_hpp */
