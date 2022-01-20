//
//  LightingSystem.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/4.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef LightingSystem_hpp
#define LightingSystem_hpp

#include <stdio.h>
#include <vector>
#include <memory>
#include "System.hpp"
#include "../Components/LightingComponent.hpp"

class World;
class LightingSystem: public System {
public:
    LightingSystem(World* world);
    void AddComponent(std::shared_ptr<LightingComponent> lightingComponent);
    std::vector<std::shared_ptr<LightingComponent>> getComponentList();
private:
    std::vector<std::shared_ptr<LightingComponent>> _mComponents;
};

#endif /* LightingSystem_hpp */
