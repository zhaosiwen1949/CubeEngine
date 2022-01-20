//
//  LightingComponent.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/4.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef LightingComponent_hpp
#define LightingComponent_hpp

#include <stdio.h>
#include <string>
#include "../Entity.hpp"

class LightingComponent: public Component {
public:
    inline static std::string GetType() {
        return _TYPE;
    }
    LightingComponent(Entity* entity);
private:
    static const std::string _TYPE;
};

#endif /* LightingComponent_hpp */
