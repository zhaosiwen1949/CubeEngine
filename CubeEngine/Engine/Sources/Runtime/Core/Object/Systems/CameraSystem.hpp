//
//  CameraSystem.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/4.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef CameraSystem_hpp
#define CameraSystem_hpp

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <memory>
#include "System.hpp"
#include "../Components/CameraComponent.hpp"
#include "../../../Utils/Camera.hpp"

class World;
class CameraSystem: public System {
public:
    CameraSystem(World* world);
    void AddComponent(std::shared_ptr<CameraComponent> cameraComponent);
    std::vector<std::shared_ptr<CameraComponent>> FindComponent(CameraComponent::CameraType type);
private:
    std::unordered_map<CameraComponent::CameraType, std::vector<std::shared_ptr<CameraComponent>>> _mComponents;
};

#endif /* CameraSystem_hpp */
