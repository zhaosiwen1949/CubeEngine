//
//  World.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/12.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <glad/glad.h>
#include "Entity.hpp"
#include "Systems/MeshRenderSystem.hpp"
#include "Systems/CameraSystem.hpp"

class Application;

class World {
public:
    World(Application* app);
    int Initialize() noexcept;
    void Finalize() noexcept;
    void Render() noexcept;
    void LoadScene(const std::string& scenePath);
    void initExample();
    inline Application* GetApp() const {
        return _mApp;
    }
    inline MeshRenderSystem* GetMeshRenderSystem() const {
        return _mMeshRenderSystem;
    }
    inline CameraSystem* GetCameraSystem() const {
        return _mCameraSystem;
    }

private:
    Application* _mApp;
    MeshRenderSystem* _mMeshRenderSystem;
    CameraSystem* _mCameraSystem;
    std::unordered_map<unsigned int, std::shared_ptr<Entity>> _mEntitiesMap;
    std::shared_ptr<Entity> _CreateEntity(World* world);
    // 临时函数，分隔 initExample 的功能
    void _initMesh();
    void _initPBRBall(const int row, const int col, const int nrRows, const int nrColumns);
    void _initPBRTextureBall(const int row, const int col, const int nrRows, const int nrColumns);
    void _initCamera();
    void _initLighting();
};

#endif /* World_hpp */
