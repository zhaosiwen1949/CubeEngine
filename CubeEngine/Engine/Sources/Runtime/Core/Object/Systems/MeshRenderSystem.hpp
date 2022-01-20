//
//  MeshRenderSystem.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/13.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef MeshRenderSystem_hpp
#define MeshRenderSystem_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <memory>
#include "System.hpp"
#include "../Components/MeshRenderComponent.hpp"

class World;
class MeshRenderSystem: public System {
public:
    MeshRenderSystem(World* world);
    void Initialize();
    void AddComponent(std::shared_ptr<MeshRenderComponent> meshRenderComponent);
    void Update();
private:
    std::vector<std::shared_ptr<MeshRenderComponent>> _mComponents;
};

#endif /* MeshRenderSystem_hpp */
