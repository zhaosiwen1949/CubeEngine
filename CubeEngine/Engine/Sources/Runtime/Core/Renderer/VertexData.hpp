//
//  VertexData.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef VertexData_hpp
#define VertexData_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct VertexData {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord0;
};

#endif /* VertexData_hpp */
