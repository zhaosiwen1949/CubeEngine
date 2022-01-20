#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord0;

out vec3 Normal;
out vec3 Position;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Position = vec3(model * vec4(aPosition, 1.0));
    Normal = mat3(model) * aNormal;
    TexCoord = aTexCoord0;
    gl_Position = projection * view * vec4(Position, 1.0);
}
