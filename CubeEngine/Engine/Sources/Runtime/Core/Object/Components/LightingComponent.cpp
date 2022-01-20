//
//  LightingComponent.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/4.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "LightingComponent.hpp"

const std::string LightingComponent::_TYPE = "LightingComponent";

LightingComponent::LightingComponent(Entity* entity):Component(_TYPE, entity) {}
