#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 uv;

layout (location = 0) out vec3 outColor;
layout (location = 1) out vec2 outTexcoord;

layout (set = 0, binding = 0) uniform CameraBuffer {
	mat4 view;
	mat4 proj;
	mat4 viewProj;
} cameraData;

//! Push constant layout 
layout (push_constant) uniform constants
{
	vec4 data;
	mat4 render_matrix;
} PushConstants;

struct ObjectData {
	mat4 modelMatrix;
};

layout(std140, set = 1, binding = 0) readonly buffer ObjectBuffer {
	ObjectData objects[];
} objectBuffer;

void main()
{
	outColor = color;
	outTexcoord = uv;
	mat4 transform = cameraData.viewProj * objectBuffer.objects[gl_BaseInstance].modelMatrix;
	gl_Position = transform * vec4(position, 1.0f);
}