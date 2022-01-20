#version 330 core

in vec3 WorldNormal;
in vec3 WorldPosition;
out vec4 FragColor;

uniform vec4 diffuseColor;
uniform vec4 lightColor;
uniform vec3 lightPosition;

void main()
{
    vec3 norm = normalize(WorldNormal);
    vec3 lightDir = normalize(lightPosition - WorldPosition);
    float diff = max(dot(lightDir, norm), 0.0);
    FragColor = diff * lightColor * diffuseColor;
}
