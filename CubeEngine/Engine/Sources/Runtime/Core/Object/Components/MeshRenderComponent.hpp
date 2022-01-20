//
//  MeshRenderComponent.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/13.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef MeshRenderComponent_hpp
#define MeshRenderComponent_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include "Component.hpp"
#include "../Entity.hpp"
#include "../../Renderer/RenderObject.hpp"
class MeshRenderComponent: public Component {
public:
    inline static std::string GetType() {
        return _TYPE;
    }
    MeshRenderComponent(Entity* entity);
    ~MeshRenderComponent() override;
    void Initialize(RenderObject* renderObject) noexcept;
    inline RenderObject* getRenderObject() const {
        return _mRenderObject;
    }
private:
    static std::string _TYPE;
    RenderObject* _mRenderObject;
};

#endif /* MeshRenderComponent_hpp */
