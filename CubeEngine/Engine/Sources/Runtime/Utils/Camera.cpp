//
//  Camera.cpp
//  CubeEngine
//
//  Created by caoyasong1949 on 2021/8/26.
//  Copyright © 2021 caoyasong1949. All rights reserved.
//

#include "Camera.hpp"

const float Camera::YAW = -90.0f;
const float Camera::PITCH = 0.0f;
const float Camera::SPEED = 2.5f;
const float Camera::SENSITIVITY = 0.1f;
const float Camera::ZOOM = 45.0f;
const float Camera::SCR_WIDTH = 800.0f;
const float Camera::SCR_HEIGHT = 600.0f;
const float Camera::SCR_NEAR = 0.1f;
const float Camera::SCR_FAR = 100.0f;

// constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Position {position}, WorldUp {up}, Yaw {yaw}, Pitch {pitch} {
    updateCameraVectors();
}

// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Position {glm::vec3(posX, posY, posZ)}, WorldUp {glm::vec3(upX, upY, upZ)}, Yaw {yaw}, Pitch {pitch} {
    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

// 返回 projection 透视矩阵
glm::mat4 Camera::GetProjectionMatrix()
{
    return glm::perspective(glm::radians((double)Zoom), (double)SCR_WIDTH/(double)SCR_HEIGHT, (double)SCR_NEAR, (double)SCR_FAR);
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessKeyRollMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MovementSpeed * 10;
    yoffset *= MovementSpeed * 10;

    Yaw   += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}


// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    float x = std::cos(glm::radians(Yaw)) * std::cos(glm::radians(Pitch));
    float y = std::sin(glm::radians(Pitch));
    float z = std::sin(glm::radians(Yaw)) * std::cos(glm::radians(Pitch));
    // 注意：这里的 x、y、z 的分量存在精读漂移的问题
    // 在值极小的时候，有可能不等于0
    glm::vec3 front { x, y, z };
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Front));
}
