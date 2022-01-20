//
//  TransformComponent.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/4.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "./Component.hpp"
#include "../Entity.hpp"

class TransformComponent: public Component {
public:
    inline static std::string GetType() {
        return _TYPE;
    }
    TransformComponent(Entity* entity);
    void Initialize(const glm::vec3& position) noexcept;
    inline glm::mat4 GetModel() const {
        return _mModel;
    }
    inline glm::vec3 GetPosition() const {
        glm::vec4 origin {0.0f, 0.0f, 0.0f, 1.0f};
        origin = _mModel * origin;
        return glm::vec3 { origin.x, origin.y, origin.z };
    }
private:
    static const std::string _TYPE;
    glm::mat4 _mModel {1.0f};
};

#endif /* TransformComponent_hpp */
