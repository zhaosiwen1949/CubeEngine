#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord0;

out vec3 WorldNormal;
out vec3 WorldPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    WorldPosition = vec3(model * vec4(aPosition, 1.0));
    WorldNormal = vec3(model * vec4(aNormal, 1.0));
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
