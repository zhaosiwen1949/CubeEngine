//
//  CameraComponent.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/4.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "CameraComponent.hpp"

const std::string CameraComponent::_TYPE = "CameraComponent";

CameraComponent::CameraComponent(Entity* entity, CameraType type, glm::vec3 position): Component(_TYPE, entity), _mType(type), camera(position) {}
