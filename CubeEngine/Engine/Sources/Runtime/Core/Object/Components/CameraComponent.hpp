//
//  CameraComponent.hpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/9/4.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#ifndef CameraComponent_hpp
#define CameraComponent_hpp

#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include "../Entity.hpp"
#include "../../../Utils/Camera.hpp"

class CameraComponent: public Component {
public:
    enum CameraType {
        MAIN = 1,
        SHADOW,
    };
    inline static std::string GetType() {
        return _TYPE;
    }
    CameraComponent(Entity* entity, CameraType type, glm::vec3 position);
    inline CameraType GetCameraType() const {
        return _mType;
    }
    inline glm::vec3 GetCameraPosition() {
        return camera.Position;
    };
    inline void UpdateCameraPosition(glm::vec3 position) {
        camera.Position = position;
    };
    inline glm::mat4 GetViewMatrix() {
        return camera.GetViewMatrix();
    };
    inline glm::mat4 GetProjectionMatrix() {
        return camera.GetProjectionMatrix();
    };
    inline void ProcessKeyboard(Camera::Camera_Movement direction, float deltaTime) {
        camera.ProcessKeyboard(direction, deltaTime);
    }
    inline void ProcessKeyRollMovement(float xoffset, float yoffset, bool constrainPitch = true) {
        camera.ProcessKeyRollMovement(xoffset, yoffset, constrainPitch);
    };
    inline void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
        camera.ProcessMouseMovement(xoffset, yoffset, constrainPitch);
    };
    inline void ProcessMouseScroll(float yoffset) {
        camera.ProcessMouseScroll(yoffset);
    };
private:
    static const std::string _TYPE;
    CameraType _mType;
    Camera camera;
};

#endif /* CameraComponent_hpp */
