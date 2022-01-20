//
//  CameraSystem.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/4.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "CameraSystem.hpp"
#include "../Components/TransformComponent.hpp"

CameraSystem::CameraSystem(World* world): System(world) {}

void CameraSystem::AddComponent(std::shared_ptr<CameraComponent> cameraComponent) {
    const auto& iter = _mComponents.find(cameraComponent->GetCameraType());
    if(iter == _mComponents.end()) {
        _mComponents.insert({cameraComponent->GetCameraType(), std::vector<std::shared_ptr<CameraComponent>> { cameraComponent }});
    }else{
        iter->second.push_back(cameraComponent);
    }
    return;
}

std::vector<std::shared_ptr<CameraComponent>> CameraSystem::FindComponent(CameraComponent::CameraType type) {
    const auto& iter = _mComponents.find(type);
    return iter->second;
}
