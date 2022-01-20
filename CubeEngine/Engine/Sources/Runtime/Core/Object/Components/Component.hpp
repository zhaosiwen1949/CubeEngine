//
//  Component.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/16.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>
#include <string>
#include "../Entity.hpp"

class Entity;
class Component {
public:
    Component(const std::string& type, Entity* entity);
    virtual ~Component() = default;
    inline std::string GetType() const {
        return _mType;
    }
    inline Entity* GetEntity() const {
        return _mEntity;
    }
    
private:
    std::string _mType;
    Entity* _mEntity;
};

#endif /* Component_hpp */
