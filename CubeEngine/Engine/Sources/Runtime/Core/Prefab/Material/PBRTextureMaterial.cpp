//
//  PBRTextureMaterial.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/10.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "PBRTextureMaterial.hpp"

#include <glm/glm.hpp>
#include "PBRTextureMaterial.hpp"
//#include "../../../Utils/Camera.hpp"

std::shared_ptr<Material> PBRTextureMaterial::getPBRTextureMaterial() {
    std::shared_ptr<Material> mPBRTextureMaterial = std::make_shared<Material>();
    mPBRTextureMaterial->Init("Asset/Shaders/PBRTextureVertex.frag", "Asset/Shaders/PBRTextureFragment.frag");
    mPBRTextureMaterial->SetVec3Property("lightColor", 300.0f, 300.0f, 300.0f);
    mPBRTextureMaterial->mRenderState->mbCull = false;
    
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f,  10.0f, 10.0f),
        glm::vec3( 10.0f,  10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3( 10.0f, -10.0f, 10.0f),
    };
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i) {
//            glm::vec3 newPos = lightPositions[i] + glm::vec3(std::sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        glm::vec3 newPos = lightPositions[i];
        mPBRTextureMaterial->SetVec3Property("lightPosition[" + std::to_string(i) + "]", newPos);
//            shader.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
    }
    
    return mPBRTextureMaterial;
}
