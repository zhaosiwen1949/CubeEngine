//
//  PBRTextureMaterial.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/10.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef PBRTextureMaterial_hpp
#define PBRTextureMaterial_hpp

#include <stdio.h>
#include <memory>
#include "../../Renderer/Material.hpp"

class PBRTextureMaterial {
public:
    static std::shared_ptr<Material> getPBRTextureMaterial();
};


#endif /* PBRTextureMaterial_hpp */
