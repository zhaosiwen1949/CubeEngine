//
//  Entity.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/13.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <unordered_map>
#include <string>
#include <memory>
#include "Components/Component.hpp"

class World;
class Component;
class Entity {
public:
    Entity(World* world);
    ~Entity();
public:
    void Initialize() noexcept;
    template<typename T, typename... Args> std::shared_ptr<T> AddComponent(Args... args) {
        const auto& iter = _mComponents.find(T::GetType());
        if(iter == _mComponents.end()) {
            std::shared_ptr<T> mComponent = std::make_shared<T>(this, args...);
            _mComponents.insert({ mComponent->GetType(), mComponent });
            return mComponent;
        } else {
            printf("不能重复添加组件");
            return std::dynamic_pointer_cast<T>(iter->second);
        }
    };
    template<typename T> std::shared_ptr<T> FindComponent() {
        const auto& iter = _mComponents.find(T::GetType());
        if(iter != _mComponents.end()) {
            return std::dynamic_pointer_cast<T>(iter->second);
        }else{
            return nullptr;
        }
    }
    
    inline World* getWorld() const {
        return mWorld;
    }
    inline unsigned int getId() const {
        return id;
    }

private:
    static unsigned int uuid;
private:
    unsigned int id;
    World* mWorld;
    std::unordered_map<std::string, std::shared_ptr<Component>> _mComponents;
};

#endif /* Entity_hpp */
