//
//  World.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/12.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "World.hpp"

World::World(Application* app) {
    mApp = app;
}

int World::Initialize() noexcept {
    return 0;
}

void World::Render() noexcept {
    glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glad_glClear(GL_COLOR_BUFFER_BIT);
}

void World::Finalize() noexcept {
    return;
}
