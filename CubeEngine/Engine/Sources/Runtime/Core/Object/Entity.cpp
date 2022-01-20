//
//  Entity.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/13.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "Entity.hpp"

Entity::Entity(World* world) {
    mWorld = world;
}

Entity::~Entity() {
    mWorld = nullptr;
    printf("Enity 触发析构");
}

unsigned int Entity::uuid = 0;

void Entity::Initialize() noexcept {
    id = uuid++;
}
