//
//  SimpleMaterial.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/19.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef SimpleMaterial_hpp
#define SimpleMaterial_hpp

#include <stdio.h>
#include <memory>
#include "../../Renderer/Material.hpp"

class SimpleMaterial {
public:
    static std::shared_ptr<Material> getSimpleMaterial();
};

#endif /* SimpleMaterial_hpp */
