//
//  Triangle.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/25.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include <vector>
#include <glad/glad.h>
#include "Triangle.hpp"
#include "../../Renderer/VertexData.hpp"

Triangle* Triangle::_mTriangle = nullptr;

Triangle* Triangle::getTriangle() {
    if(_mTriangle == nullptr) {
        float data[] = {
            // front face
            -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-right
            0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // top-right
        };
        
        std::vector<VertexData> vertices;
        unsigned int stride = 8;
        for(unsigned int i = 0; i < 3 ; i++) {
            unsigned int n = i * stride;
            VertexData vertex;
            vertex.position.x = data[n];
            vertex.position.y = data[n+1];
            vertex.position.z = data[n+2];
            vertex.normal.x = data[n+3];
            vertex.normal.y = data[n+4];
            vertex.normal.z = data[n+5];
            vertex.texcoord0.x = data[n+6];
            vertex.texcoord0.y = data[n+7];
            vertices.push_back(vertex);
        }
        
        std::vector<unsigned int> indices = {0, 1, 2};
        
        _mTriangle = new Triangle;
        _mTriangle->mVAO = new VertexArrayObject;
        _mTriangle->mVAO->SetVBO(GL_TRIANGLES, vertices);
        _mTriangle->mVAO->SetIBO(GL_TRIANGLES, indices);
    }

    return _mTriangle;
}
