//
//  Component.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/16.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "Component.hpp"

Component::Component(const std::string& type, Entity* entity): _mType(type), _mEntity(entity) {}
