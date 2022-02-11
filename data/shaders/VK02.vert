//
#version 460

layout(location = 0) out vec3 uvw;

struct ImDrawVert   { float x, y, z; float u, v; float nx, ny, nz; };
struct DrawData {
	uint mesh;
	uint material;
	uint lod;
	uint indexOffset;
	uint vertexOffset;
	uint transformIndex;
};
struct MaterialData { uint tex2D; };

layout(binding = 0) uniform  UniformBuffer { mat4 proj; mat4 view; vec4 cameraPos; } ubo;
layout(binding = 1) readonly buffer SBO    { ImDrawVert data[]; } sbo;
layout(binding = 2) readonly buffer IBO    { uint   data[]; } ibo;
layout(binding = 3) readonly buffer DrawBO { DrawData data[]; } drawDataBuffer;
layout(binding = 5) readonly buffer XfrmBO { mat4 data[]; } transformBuffer;

void main()
{
	DrawData dd = drawDataBuffer.data[gl_BaseInstance];

	uint refIdx = dd.indexOffset + gl_VertexIndex;
	ImDrawVert v = sbo.data[ibo.data[refIdx] + dd.vertexOffset];

	uvw = normalize(vec3(v.x, v.y, v.z));

	mat4 model = transformBuffer.data[gl_BaseInstance];

	vec4 v_worldPos  = model * vec4(v.x, v.y, v.z, 1.0);

	/* Assign shader outputs */
	gl_Position = ubo.proj * ubo.view * v_worldPos;
}
