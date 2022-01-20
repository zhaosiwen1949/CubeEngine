//
//  PhongDiffuseMaterial.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/1.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//
#include <glm/glm.hpp>
#include "PhongDiffuseMaterial.hpp"
#include "../../../Utils/Camera.hpp"


std::shared_ptr<Material> PhongDiffuseMaterial::getPhongDiffuseMaterial() {
    std::shared_ptr<Material> mPhongDiffuseMaterial = std::make_shared<Material>();
    mPhongDiffuseMaterial->Init("Asset/Shaders/phongDiffuseVertex.frag", "Asset/Shaders/phongDiffuseFragment.frag");
    mPhongDiffuseMaterial->SetVec4Property("diffuseColor", 1.0f, 0.0f, 0.0f, 1.0f);
    mPhongDiffuseMaterial->SetVec4Property("lightColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mPhongDiffuseMaterial->SetVec3Property("lightPosition", 5.0f, 5.0f, 0.0f);
    return mPhongDiffuseMaterial;
}
