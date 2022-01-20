//
//  SimpleMaterial.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/19.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include <glm/glm.hpp>
#include "SimpleMaterial.hpp"
#include "../../../Utils/Camera.hpp"

std::shared_ptr<Material> SimpleMaterial::getSimpleMaterial() {
    std::shared_ptr<Material> mSimpleMaterial = std::make_shared<Material>();
    mSimpleMaterial->Init("Asset/Shaders/simpleVertex.frag", "Asset/Shaders/simpleFragment.frag");
    mSimpleMaterial->SetVec4Property("uColor", 0.0f, 1.0f, 0.0f, 1.0f);
    return mSimpleMaterial;
}
