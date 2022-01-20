//
//  UniformBinder.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/18.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "UniformBinder.hpp"

UniformBinder::UniformBinder(GLuint location, SetUniformUpdater updateFn, std::shared_ptr<MaterialProperty> materialProperty): _mLocation(location), _mUpdateFn(updateFn), _mMaterialProperty(materialProperty) {}

void UniformBinder::Bind() {
    _mUpdateFn(_mLocation, _mMaterialProperty);
}

void UniformBinder::UpdateVec4(GLuint location, std::shared_ptr<MaterialProperty> materialProperty) {
    std::shared_ptr<UniformVector4Property> property = std::dynamic_pointer_cast<UniformVector4Property>(materialProperty);
    glad_glUniform4fv(location, 1, glm::value_ptr(property->GetValue()));
}

void UniformBinder::UpdateVec3(GLuint location, std::shared_ptr<MaterialProperty> materialProperty) {
    std::shared_ptr<UniformVector3Property> property = std::dynamic_pointer_cast<UniformVector3Property>(materialProperty);
    glad_glUniform3fv(location, 1, glm::value_ptr(property->GetValue()));
}

void UniformBinder::UpdateMat4(GLuint location, std::shared_ptr<MaterialProperty> materialProperty) {
    std::shared_ptr<UniformMatrix4Property> property = std::dynamic_pointer_cast<UniformMatrix4Property>(materialProperty);
    glad_glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(property->GetValue()));
}

void UniformBinder::UpdateFloat(GLuint location, std::shared_ptr<MaterialProperty> materialProperty) {
    std::shared_ptr<UniformFloatProperty> property = std::dynamic_pointer_cast<UniformFloatProperty>(materialProperty);
    glad_glUniform1f(location, property->GetValue());
}

void UniformBinder::UpdateTexture(GLuint location, std::shared_ptr<MaterialProperty> materialProperty) {
    std::shared_ptr<UniformTextureProperty> property = std::dynamic_pointer_cast<UniformTextureProperty>(materialProperty);
    if(property->GetTexture() != nullptr && property->GetSlot() != -1) {
        glad_glActiveTexture(GL_TEXTURE0 + property->GetSlot());
        glad_glBindTexture(property->GetTexture()->GetTextureType(), property->GetTexture()->GetTextureID());
        glad_glUniform1i(location, property->GetSlot());
    } else {
        printf("纹理属性 %s 不存在对应的纹理贴图", property->GetName().c_str());
    }
}
