#version 450
#extension GL_ARB_separate_shader_objects : enable
layout(binding = 0) uniform UniformBufferObject {
  mat4 model;
  mat4 view;
  mat4 proj;
} ubo;

out gl_PerVertex {
  vec4 gl_Position;
};

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

layout (location = 0) out vec3 outWorldPos;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out vec2 outUV;
layout(location = 3) out vec3 outViewPos;

void main()
{
  outWorldPos =  vec3(ubo.model * vec4(pos, 1));
  outNormal = mat3(transpose(inverse(ubo.model))) * normal;
  outUV = texCoord;
  outViewPos = vec3(inverse(ubo.view)[3]);

  gl_Position = ubo.proj * ubo.view * ubo.model * vec4(pos, 1);
}
