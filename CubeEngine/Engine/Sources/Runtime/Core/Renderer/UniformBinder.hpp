//
//  UniformBinder.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef UniformBinder_hpp
#define UniformBinder_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "MaterialProperty.hpp"
#include "../../Utils/LinkedList.hpp"

// TO DO: 可以增加 Camera 类
typedef void(* SetUniformUpdater)(GLuint location, std::shared_ptr<MaterialProperty> materialProperty);


class UniformBinder: public LinkedList {
public:
    UniformBinder(GLuint location, SetUniformUpdater updateFn, std::shared_ptr<MaterialProperty> materialProperty);
    inline std::shared_ptr<MaterialProperty> GetMaterialProperty() const {
        return _mMaterialProperty;
    }
    void Bind();
    static void UpdateVec4(GLuint location, std::shared_ptr<MaterialProperty> materialProperty);
    static void UpdateVec3(GLuint location, std::shared_ptr<MaterialProperty> materialProperty);
    static void UpdateMat4(GLuint location, std::shared_ptr<MaterialProperty> materialProperty);
    static void UpdateFloat(GLuint location, std::shared_ptr<MaterialProperty> materialProperty);
    static void UpdateTexture(GLuint location, std::shared_ptr<MaterialProperty> materialProperty);
private:
    // Location
    GLuint _mLocation;
    
    // Property
    std::shared_ptr<MaterialProperty> _mMaterialProperty;
    
    // UpdateFn
    SetUniformUpdater _mUpdateFn;
};

#endif /* UniformBinder_hpp */
