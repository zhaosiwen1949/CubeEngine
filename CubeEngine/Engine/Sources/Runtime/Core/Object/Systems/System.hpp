//
//  System.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/6.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef System_hpp
#define System_hpp

#include <stdio.h>

class World;
class System {
public:
    System(World* world);
    inline World* GetWorld() const {
        return _mWorld;
    }
private:
    World* _mWorld;
};

#endif /* System_hpp */
