//
//  Sphere.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/19.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include <vector>
#include <glad/glad.h>
#include "Sphere.hpp"
#include "../../Renderer/VertexData.hpp"

Sphere* Sphere::_mSphere = nullptr;

Sphere* Sphere::getSphere() {
    if(_mSphere == nullptr) {
        SetVAO1();
//        SetVAO2();
    }

    return _mSphere;
}

void Sphere::SetVAO1() {
    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359;
    
    std::vector<VertexData> vertices;
    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            
            VertexData vertex;
            vertex.position.x = xPos;
            vertex.position.y = yPos;
            vertex.position.z = zPos;
            vertex.normal.x = xPos;
            vertex.normal.y = yPos;
            vertex.normal.z = zPos;
            vertex.texcoord0.x = xSegment;
            vertex.texcoord0.y = ySegment;
            
            vertices.push_back(vertex);
        }
    }
    
    std::vector<unsigned int> indices;
    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow) // even rows: y == 0, y == 2; and so on
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y       * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y       * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
    
    _mSphere = new Sphere;
    _mSphere->mVAO = new VertexArrayObject;
    _mSphere->mVAO->SetVBO(GL_TRIANGLES, vertices);
    _mSphere->mVAO->SetIBO(GL_TRIANGLE_STRIP, indices);
}

void Sphere::SetVAO2() {
    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359;
    
    std::vector<VertexData> vertices;
    std::vector<unsigned int> indices;

    /*2-计算球体顶点*/
    //生成球的顶点
    for (int y=0;y<=Y_SEGMENTS;y++)
    {
        for (int x=0;x<=X_SEGMENTS;x++)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            VertexData vertex;
            vertex.position.x = xPos;
            vertex.position.y = yPos;
            vertex.position.z = zPos;
            vertex.normal.x = xPos;
            vertex.normal.y = yPos;
            vertex.normal.z = zPos;
            vertex.texcoord0.x = xSegment;
            vertex.texcoord0.y = ySegment;
            
            vertices.push_back(vertex);
        }
    }

    //生成球的Indices
    for (unsigned int i=0;i<Y_SEGMENTS;i++)
    {
        for (unsigned int j=0;j<X_SEGMENTS;j++)
        {
            indices.push_back(i * (X_SEGMENTS + 1) + j);
            indices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
            indices.push_back((i + 1) * (X_SEGMENTS + 1) + j+1);
            indices.push_back(i* (X_SEGMENTS + 1) + j);
            indices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
            indices.push_back(i * (X_SEGMENTS + 1) + j + 1);
        }
    }
    
    _mSphere = new Sphere;
    _mSphere->mVAO = new VertexArrayObject;
    _mSphere->mVAO->SetVBO(GL_TRIANGLES, vertices);
    _mSphere->mVAO->SetIBO(GL_TRIANGLES, indices);
}
