//
//  World.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/12.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <glad/glad.h>

class Application;

class World {
public:
    Application* mApp;
public:
    World(Application* app);
    int Initialize() noexcept;
    void Finalize() noexcept;
    void Render() noexcept;
};

#endif /* World_hpp */
