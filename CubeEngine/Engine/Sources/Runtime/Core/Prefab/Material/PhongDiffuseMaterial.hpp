//
//  PhongDiffuseMaterial.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/1.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef PhongDiffuseMaterial_hpp
#define PhongDiffuseMaterial_hpp

#include <stdio.h>
#include <memory>
#include "../../Renderer/Material.hpp"

class PhongDiffuseMaterial {
public:
    static std::shared_ptr<Material> getPhongDiffuseMaterial();
};

#endif /* PhongDiffuseMaterial_hpp */
