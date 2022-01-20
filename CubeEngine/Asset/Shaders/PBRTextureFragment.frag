#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 Position;
in vec2 TexCoord;

uniform vec3 lightColor;
uniform vec3 lightPosition[4];
uniform vec3 cameraPosition;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

const float PI = 3.14159265359;

vec3 getNormalFromMap() {
    vec3 tangentNormal = texture(normalMap, TexCoord).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(Position);
    vec3 Q2  = dFdy(Position);
    vec2 st1 = dFdx(TexCoord);
    vec2 st2 = dFdy(TexCoord);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

vec3 FresnelSchlick(vec3 F0, float cosTheta) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(float NdotH, float roughness) {
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(float NdotL, float NdotV, float roughness)
{
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main()
{
    vec3 albedo     = pow(texture(albedoMap, TexCoord).rgb, vec3(2.2));
    float metallic  = texture(metallicMap, TexCoord).r;
    float roughness = texture(roughnessMap, TexCoord).r;
    float ao        = texture(aoMap, TexCoord).r;
    
    vec3 N = getNormalFromMap();
    vec3 V = normalize(cameraPosition - Position);
    
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < 4; ++i) {
        // 前置变量
        vec3 L = normalize(lightPosition[i] - Position);
        vec3 H = normalize(V + L);
        float NdotL = max(dot(N, L), 0.0);
        float NdotV = max(dot(N, V), 0.0);
        float HdotV = max(dot(H, V), 0.0);
        float NdotH = max(dot(N, H), 0.0);
        
        float distance = length(lightPosition[i] - Position);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColor * attenuation;
        
        // 计算 BRDF 反射部分
        // 计算菲涅尔反射项
        vec3 F0 = vec3(0.04);
        F0 = mix(F0, albedo, metallic);
        vec3 F = FresnelSchlick(F0, HdotV);
        
        // 计算法线分布，采用 GGX 方法
        float NDF = DistributionGGX(NdotH, roughness);
        
        // 计算几何遮挡项
        float G = GeometrySmith(NdotL, NdotV, roughness);
        
        vec3 nominator = NDF * G * F;
        float denominator = 4.0 * NdotV * NdotL;
        vec3 specular = nominator / max(denominator, 0.001);
        
        // 计算 BRDF 散射部分
        vec3 kS = F; // 菲涅尔项，代表光的能量中，被反射的部分
        vec3 kD = vec3(1.0) - kS; // 反射剩余的部分，认为参入光的散射
        kD *= 1.0 - metallic; // 剩余能量中，只有非金属的部分，会发生散射
        vec3 diffuse = kD * albedo / PI;
        
        Lo += (diffuse + specular) * radiance * NdotL;
    }
    
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;
    
    // HDR toneMapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2));
    FragColor = vec4(color, 1.0);
}
