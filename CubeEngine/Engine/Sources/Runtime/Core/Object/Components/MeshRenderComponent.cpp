//
//  MeshRenderComponent.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/13.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "MeshRenderComponent.hpp"
//#include "../World.hpp"

std::string MeshRenderComponent::_TYPE = "MeshRenderComponent";

MeshRenderComponent::MeshRenderComponent(Entity* entity):Component(_TYPE, entity) {}

MeshRenderComponent::~MeshRenderComponent() {
    delete _mRenderObject;
    _mRenderObject = nullptr;
}

void MeshRenderComponent::Initialize(RenderObject* renderObject) noexcept {
    _mRenderObject = renderObject;
}
