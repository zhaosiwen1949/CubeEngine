//
#version 460

#extension GL_EXT_nonuniform_qualifier : require

#include <data/shaders/Common/VK01.h>
#include <data/shaders/Common/VK01_VertCommon.h>
#include <data/shaders/Common/AlphaTest.h>

layout(location = 0) in vec3 uvw;
layout(location = 1) in vec3 v_worldNormal;
layout(location = 2) in vec4 v_worldPos;
layout(location = 3) in flat uint matIdx;

layout(location = 0) out vec4 outColor;

// Buffer with PBR material coefficients
layout(binding = 4) readonly buffer MatBO  { MaterialData data[]; } mat_bo;

layout(binding = 6) uniform samplerCube texEnvMap;
layout(binding = 7) uniform samplerCube texEnvMapIrradiance;
layout(binding = 8) uniform sampler2D   texBRDF_LUT;

// All 2D textures for all of the materials
layout(binding = 9) uniform sampler2D textures[];

#include <data/shaders/Common/PBR.h>

void main()
{
	MaterialData md = mat_bo.data[matIdx];

	vec4 ao = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 emission = vec4(0.0, 0.0, 0.0, 0.0); // md.emissiveColor_;
	vec4 albedo = md.albedoColor_;
	vec3 normalSample = vec3(0.0, 0.0, 0.0);
	vec4 mrSample = vec4(0.0, 1.0, 0.0, 0.0);

	const int INVALID_HANDLE = 2000;

	// 读取材质属性
	if (md.ambientOcclusionMap_ < INVALID_HANDLE)
	{
		uint texIdx = uint(md.ambientOcclusionMap_);
		ao = texture(textures[nonuniformEXT(texIdx)], uvw.xy);
	}
	if (md.emissiveMap_ < INVALID_HANDLE)
	{
		uint texIdx = uint(md.emissiveMap_);
		emission = texture(textures[nonuniformEXT(texIdx)], uvw.xy);
	}
	if (md.albedoMap_ < INVALID_HANDLE)
	{
		uint texIdx = uint(md.albedoMap_);
		albedo = texture(textures[nonuniformEXT(texIdx)], uvw.xy);
	}
	if (md.normalMap_ < INVALID_HANDLE)
	{
		uint texIdx = uint(md.normalMap_);
		normalSample = texture(textures[nonuniformEXT(texIdx)], uvw.xy).xyz;
	}
	if (md.metallicRoughnessMap_ < INVALID_HANDLE)
	{
		uint texIdx = uint(md.metallicRoughnessMap_);
		mrSample = texture(textures[nonuniformEXT(texIdx)], uvw.xy);
	}

	runAlphaTest(albedo.a, md.alphaTest_);

	// 颜色校正
	emission.rgb = SRGBtoLINEAR(emission).rgb;
	albedo.rgb = SRGBtoLINEAR(albedo).rgb;

	// 计算法线
	vec3 n = normalize(v_worldNormal);

	// normal mapping: skip missing normal maps
	if (length(normalSample) > 0.5)
	{
		n = perturbNormal(n, normalize(ubo.cameraPos.xyz - v_worldPos.xyz), normalSample, uvw.xy);
	}

	// 写死一个光照方向
	vec3 lightDir = normalize(vec3(-1.0, -1.0, 0.1));

	// 设置 PBR 渲染所需要的数据
	PBRInfo pbrInputs;

	// image-based lighting
	vec3 color = calculatePBRInputsMetallicRoughness(albedo, n, ubo.cameraPos.xyz, v_worldPos.xyz, mrSample, pbrInputs);

	// one hardcoded light source
	color += calculatePBRLightContribution( pbrInputs, lightDir, vec3(1.0) );

	// ambient occlusion
	color = color * ( ao.r < 0.01 ? 1.0 : ao.r );

	// emissive
	color = pow( emission.rgb + color, vec3(1.0/2.2) );

	outColor = vec4(color, 1.0);
//	outColor = vec4(emission.rgb, 1.0);
//	outColor = vec4(albedo.rgb, 1.0);
//	outColor = vec4(n, 1.0);
//	outColor = vec4(normalSample, 1.0);
//	outColor = vec4(normalize(ubo.cameraPos.xyz - v_worldPos.xyz), 1.0);
}
