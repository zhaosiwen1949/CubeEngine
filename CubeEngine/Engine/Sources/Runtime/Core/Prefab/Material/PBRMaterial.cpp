//
//  PBRMaterial.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/2.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include <glm/glm.hpp>
#include "PBRMaterial.hpp"
//#include "../../../Utils/Camera.hpp"

std::shared_ptr<Material> PBRMaterial::getPBRMaterial() {
    std::shared_ptr<Material> mPBRMaterial = std::make_shared<Material>();
    mPBRMaterial->Init("Asset/Shaders/PBRVertex.frag", "Asset/Shaders/PBRFragment.frag");
    mPBRMaterial->SetVec3Property("albedo", 0.5f, 0.0f, 0.0f);
    mPBRMaterial->SetFloatProperty("ao", 1.0f);
    mPBRMaterial->SetVec3Property("lightColor", 300.0f, 300.0f, 300.0f);
    mPBRMaterial->mRenderState->mbCull = false;
    
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f,  10.0f, 10.0f),
        glm::vec3( 10.0f,  10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3( 10.0f, -10.0f, 10.0f),
    };
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i) {
//            glm::vec3 newPos = lightPositions[i] + glm::vec3(std::sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        glm::vec3 newPos = lightPositions[i];
        mPBRMaterial->SetVec3Property("lightPosition[" + std::to_string(i) + "]", newPos);
//            shader.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
    }
    
    return mPBRMaterial;
}
