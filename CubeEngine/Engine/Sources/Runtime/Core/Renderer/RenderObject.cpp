//
//  RenderObject.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "RenderObject.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

RenderObject::RenderObject(VertexArrayObject* vao, std::shared_ptr<Material> material): _mVAO(vao), _mMaterial(material) {
    // TO DO: 这里的 VAO 可以做成缓存式的
    // 同样的 VBO 和 IBO，对应同样的 VAO，而且初始化过的 VAO，还能避免再次被初始化
    _mVAO->Init();
}

RenderObject::~RenderObject() {
    delete _mVAO;
    _mVAO = nullptr;
}

void RenderObject::Run(RenderData renderData) {
    _mVAO->Bind();

    // 绑定材质
    if(_mMaterial != nullptr) {
        // 设置 MVP 矩阵
        _mMaterial->SetMat4Property("model", renderData.model);
        _mMaterial->SetMat4Property("view", renderData.view);
        _mMaterial->SetMat4Property("projection", renderData.projection);
        _mMaterial->SetVec3Property("cameraPosition", renderData.cameraPosition);
        
        _mMaterial->Bind();
    } else {
        printf("不存在 Material，停止渲染");
        return;
    }

    // DrawCall
    _mVAO->Draw();
    
    _mVAO->UnBind();
}
