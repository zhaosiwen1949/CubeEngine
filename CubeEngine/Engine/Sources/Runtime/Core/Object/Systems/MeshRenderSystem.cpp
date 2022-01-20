//
//  MeshRenderSystem.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/13.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "MeshRenderSystem.hpp"
#include "CameraSystem.hpp"
#include "../World.hpp"
#include "../Components/CameraComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../../Renderer/RenderState.hpp"

MeshRenderSystem::MeshRenderSystem(World* world): System(world) {}

void MeshRenderSystem::Initialize() {
    GlobalRenderState::Init();
}

void MeshRenderSystem::AddComponent(std::shared_ptr<MeshRenderComponent> meshRenderComponent) {
    _mComponents.push_back(meshRenderComponent);
    return;
}

void MeshRenderSystem::Update() {
    GlobalRenderState::ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    GlobalRenderState::ClearZ();

    // Camera 获取主相机位置、视椎变换 - project、view、cameraPosition
    CameraSystem* camSys = GetWorld()->GetCameraSystem();
    std::shared_ptr<CameraComponent> mainCamera = camSys->FindComponent(CameraComponent::MAIN)[0];
    glm::mat4 view = mainCamera->GetViewMatrix();
    glm::mat4 projection = mainCamera->GetProjectionMatrix();
    glm::vec3 cameraPosition = mainCamera->GetCameraPosition();
    
    // Lighting 获取光源位置、颜色等属性 - lightingPosition、lightingColor
    for(std::shared_ptr<MeshRenderComponent> comp : _mComponents){
        // Transform 获取 MeshRender 的 位置 - model
        std::shared_ptr<TransformComponent> transComp = comp->GetEntity()->FindComponent<TransformComponent>();
        glm::mat4 model = transComp->GetModel();
        comp->getRenderObject()->Run({model, view, projection, cameraPosition});
    }
}
