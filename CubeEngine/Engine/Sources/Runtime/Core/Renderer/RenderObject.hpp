//
//  RenderObject.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef RenderObject_hpp
#define RenderObject_hpp

#include <stdio.h>
#include <memory>
#include <glm/glm.hpp>
#include "VertexArrayObject.hpp"
#include "Material.hpp"

class RenderObject {
public:
    struct RenderData {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 cameraPosition;
    };
    RenderObject(VertexArrayObject* vao, std::shared_ptr<Material> material);
    ~RenderObject();
    void Run(RenderData renderData);
private:
    // VAO
    // TO DO: 建议改为智能指针，防止内存泄漏
    VertexArrayObject* _mVAO;
    
    // Material
    std::shared_ptr<Material> _mMaterial;
};

#endif /* RenderObject_hpp */
