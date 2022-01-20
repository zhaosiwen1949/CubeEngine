//
//  TransformComponent.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/4.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "TransformComponent.hpp"

const std::string TransformComponent::_TYPE = "TransformComponent";

TransformComponent::TransformComponent(Entity* entity):Component(_TYPE, entity) {}

void TransformComponent::Initialize(const glm::vec3& position) noexcept {
    _mModel = glm::translate(_mModel, position);
};


