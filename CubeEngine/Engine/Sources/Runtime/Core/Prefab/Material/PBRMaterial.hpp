//
//  PBRMaterial.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/2.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef PBRMaterial_hpp
#define PBRMaterial_hpp

#include <stdio.h>
#include <memory>
#include "../../Renderer/Material.hpp"

class PBRMaterial {
public:
    static std::shared_ptr<Material> getPBRMaterial();
};

#endif /* PBRMaterial_hpp */
