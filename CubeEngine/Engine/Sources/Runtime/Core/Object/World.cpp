//
//  World.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/12.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "World.hpp"
#include "./Components/MeshRenderComponent.hpp"
#include "./Components/TransformComponent.hpp"
#include "./Components/CameraComponent.hpp"
#include "./Components/LightingComponent.hpp"
#include "../Renderer/RenderObject.hpp"
#include "../Prefab/Mesh/Sphere.hpp"
//#include "../Prefab/Mesh/Triangle.hpp"
//#include "../Prefab/Mesh/Cube.hpp"
#include "../Prefab/Material/SimpleMaterial.hpp"
//#include "../Prefab/Material/PhongDiffuseMaterial.hpp"
#include "../Prefab/Material/PBRMaterial.hpp"
#include "../Prefab/Material/PBRTextureMaterial.hpp"


World::World(Application* app) {
    _mApp = app;
}

int World::Initialize() noexcept {
    // 初始化 Systems
    _mMeshRenderSystem = new MeshRenderSystem(this);
    _mMeshRenderSystem->Initialize();
    
    _mCameraSystem = new CameraSystem(this);
    
    return 0;
}

void World::Render() noexcept {
    // MeshRenderSystem 渲染
    _mMeshRenderSystem->Update();
}

void World::Finalize() noexcept {   
    return;
}

std::shared_ptr<Entity> World::_CreateEntity(World* world) {
    std::shared_ptr<Entity> entity = std::make_shared<Entity>(world);
    entity->Initialize();
    _mEntitiesMap.insert({entity->getId(), entity});
    return entity;
}

void World::LoadScene(const std::string& scenePath) {
//    Assimp::Importer importer;
//    const aiScene* scene = importer.ReadFile(scenePath,
//                                             aiProcess_CalcTangentSpace |
//                                             aiProcess_Triangulate |
//                                             aiProcess_JoinIdenticalVertices |
//                                             aiProcess_SortByPType);
    
    // 解析 scene
    // 1、MeshRenderSystem 加载全部 mesh
    
    // 2、配置 camera
    
    // 3、配置 Entity
}

void World::initExample() {
    // 创建渲染物体
    _initMesh();
    
    // 创建相机
    _initCamera();

    // 创建光源
    _initLighting();
}

void World::_initMesh() {
    const int nrRows    = 7;
    const int nrColumns = 7;
    for(int row = 0; row < nrRows; ++row) {
        for(int col = 0; col < nrColumns; ++col) {
//            _initPBRBall(row, col, nrRows, nrColumns);
            _initPBRTextureBall(row, col, nrRows, nrColumns);
        }
    }
}


void World::_initPBRBall(const int row, const int col, const int nrRows, const int nrColumns) {
    float spacing = 2.5;
    // 1、创建一个 Entity，并保存到 mEntitiesMap 中
    std::shared_ptr<Entity> entity = _CreateEntity(this);
    
    // 2、Entity 添加 MeshRenderComponent
    // TO DO: 这里可以封装下，把 AddComponent 都移到 World 里面
    std::shared_ptr<MeshRenderComponent> meshComp = entity->AddComponent<MeshRenderComponent>();
    _mMeshRenderSystem->AddComponent(meshComp);
    
    // 3、配置 MeshRenderComponent 的 renderObject
    Sphere* ball = Sphere::getSphere();
    std::shared_ptr<Material> pbrMet = PBRMaterial::getPBRMaterial();
    
    // 设置 PBR 材质的属性
    pbrMet->SetFloatProperty("metallic", (float)row / (float)nrRows);
    pbrMet->SetFloatProperty("roughness", (float)col / (float)nrColumns);
    
    RenderObject* renderObject = new RenderObject(ball->mVAO, pbrMet);
    meshComp->Initialize(renderObject);
    
    // 4、添加 TranformComponent，赋予 Entity 位置
    std::shared_ptr<TransformComponent> transComp = entity->AddComponent<TransformComponent>();
    // 初始化位置
    transComp->Initialize(glm::vec3(
        (col - (nrColumns / 2)) * spacing,
        (row - (nrRows / 2)) * spacing,
        0.0f
    ));
}

void World::_initPBRTextureBall(const int row, const int col, const int nrRows, const int nrColumns) {
    float spacing = 2.5;
    // 1、创建一个 Entity，并保存到 mEntitiesMap 中
    std::shared_ptr<Entity> entity = _CreateEntity(this);
    
    // 2、Entity 添加 MeshRenderComponent
    // TO DO: 这里可以封装下，把 AddComponent 都移到 World 里面
    std::shared_ptr<MeshRenderComponent> meshComp = entity->AddComponent<MeshRenderComponent>();
    _mMeshRenderSystem->AddComponent(meshComp);
    
    // 3、配置 MeshRenderComponent 的 renderObject
    Sphere* ball = Sphere::getSphere();
    std::shared_ptr<Material> pbrTexMet = PBRTextureMaterial::getPBRTextureMaterial();
    
    // 设置 PBR 材质的属性
    switch (row % 5) {
        case 0:
            pbrTexMet->SetTextureProperty("albedoMap", Texture2D::LoadTexture("Asset/Textures/pbr/wall/albedo.png"));
            pbrTexMet->SetTextureProperty("metallicMap", Texture2D::LoadTexture("Asset/Textures/pbr/wall/metallic.png"));
            pbrTexMet->SetTextureProperty("normalMap", Texture2D::LoadTexture("Asset/Textures/pbr/wall/normal.png"));
            pbrTexMet->SetTextureProperty("aoMap", Texture2D::LoadTexture("Asset/Textures/pbr/wall/ao.png"));
            pbrTexMet->SetTextureProperty("roughnessMap", Texture2D::LoadTexture("Asset/Textures/pbr/wall/roughness.png"));
            break;
        
        case 1:
            pbrTexMet->SetTextureProperty("albedoMap", Texture2D::LoadTexture("Asset/Textures/pbr/rusted_iron/albedo.png"));
            pbrTexMet->SetTextureProperty("metallicMap", Texture2D::LoadTexture("Asset/Textures/pbr/rusted_iron/metallic.png"));
            pbrTexMet->SetTextureProperty("normalMap", Texture2D::LoadTexture("Asset/Textures/pbr/rusted_iron/normal.png"));
            pbrTexMet->SetTextureProperty("aoMap", Texture2D::LoadTexture("Asset/Textures/pbr/rusted_iron/ao.png"));
            pbrTexMet->SetTextureProperty("roughnessMap", Texture2D::LoadTexture("Asset/Textures/pbr/rusted_iron/roughness.png"));
            break;
        
        case 2:
            pbrTexMet->SetTextureProperty("albedoMap", Texture2D::LoadTexture("Asset/Textures/pbr/grass/albedo.png"));
            pbrTexMet->SetTextureProperty("metallicMap", Texture2D::LoadTexture("Asset/Textures/pbr/grass/metallic.png"));
            pbrTexMet->SetTextureProperty("normalMap", Texture2D::LoadTexture("Asset/Textures/pbr/grass/normal.png"));
            pbrTexMet->SetTextureProperty("aoMap", Texture2D::LoadTexture("Asset/Textures/pbr/grass/ao.png"));
            pbrTexMet->SetTextureProperty("roughnessMap", Texture2D::LoadTexture("Asset/Textures/pbr/grass/roughness.png"));
            break;
        
        case 3:
            pbrTexMet->SetTextureProperty("albedoMap", Texture2D::LoadTexture("Asset/Textures/pbr/gold/albedo.png"));
            pbrTexMet->SetTextureProperty("metallicMap", Texture2D::LoadTexture("Asset/Textures/pbr/gold/metallic.png"));
            pbrTexMet->SetTextureProperty("normalMap", Texture2D::LoadTexture("Asset/Textures/pbr/gold/normal.png"));
            pbrTexMet->SetTextureProperty("aoMap", Texture2D::LoadTexture("Asset/Textures/pbr/gold/ao.png"));
            pbrTexMet->SetTextureProperty("roughnessMap", Texture2D::LoadTexture("Asset/Textures/pbr/gold/roughness.png"));
            break;
        
        case 4:
            pbrTexMet->SetTextureProperty("albedoMap", Texture2D::LoadTexture("Asset/Textures/pbr/plastic/albedo.png"));
            pbrTexMet->SetTextureProperty("metallicMap", Texture2D::LoadTexture("Asset/Textures/pbr/plastic/metallic.png"));
            pbrTexMet->SetTextureProperty("normalMap", Texture2D::LoadTexture("Asset/Textures/pbr/plastic/normal.png"));
            pbrTexMet->SetTextureProperty("aoMap", Texture2D::LoadTexture("Asset/Textures/pbr/plastic/ao.png"));
            pbrTexMet->SetTextureProperty("roughnessMap", Texture2D::LoadTexture("Asset/Textures/pbr/plastic/roughness.png"));
            break;
            
        default:
            break;
    }
    
    RenderObject* renderObject = new RenderObject(ball->mVAO, pbrTexMet);
    meshComp->Initialize(renderObject);
    
    // 4、添加 TranformComponent，赋予 Entity 位置
    std::shared_ptr<TransformComponent> transComp = entity->AddComponent<TransformComponent>();
    // 初始化位置
    transComp->Initialize(glm::vec3(
        (col - (nrColumns / 2)) * spacing,
        (row - (nrRows / 2)) * spacing,
        0.0f
    ));
}

void World::_initCamera() {
    // 1、创建一个 Entity，并保存到 mEntitiesMap 中
    std::shared_ptr<Entity> entity = _CreateEntity(this);
    
    // 2、添加 CameraComponent
    std::shared_ptr<CameraComponent> camComp = entity->AddComponent<CameraComponent>(CameraComponent::MAIN, glm::vec3(0.0, 0.0, 3.0));
    _mCameraSystem->AddComponent(camComp);
}

void World::_initLighting() {
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f,  10.0f, 10.0f),
        glm::vec3( 10.0f,  10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3( 10.0f, -10.0f, 10.0f),
    };
    
    for(unsigned int i = 0; i < 4; ++i) {
        // 1、创建一个 Entity，并保存到 mEntitiesMap 中
        std::shared_ptr<Entity> entity = _CreateEntity(this);
        
        // 2、添加 LightingComponent
        std::shared_ptr<LightingComponent> lightComp = entity->AddComponent<LightingComponent>();
        
        // 3、添加 MeshRenderComponent
        std::shared_ptr<MeshRenderComponent> meshComp = entity->AddComponent<MeshRenderComponent>();
        _mMeshRenderSystem->AddComponent(meshComp);
        
        // 4、配置 MeshRenderComponent 的 renderObject
        Sphere* ball = Sphere::getSphere();
        std::shared_ptr<Material> sMet = SimpleMaterial::getSimpleMaterial();
        
        RenderObject* renderObject = new RenderObject(ball->mVAO, sMet);
        meshComp->Initialize(renderObject);
        
        // 5、添加 TranformComponent，赋予 Entity 位置
        std::shared_ptr<TransformComponent> transComp = entity->AddComponent<TransformComponent>();
        // 初始化位置
        transComp->Initialize(lightPositions[i]);
    }
}
