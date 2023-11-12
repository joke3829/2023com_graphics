#version 330 core

in vec3 vPos;
in vec3 vColor;
out vec3 PassColor;

uniform mat4 transform;
uniform mat4 world_rotate;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * world_rotate * transform * vec4(vPos, 1.0f);
	PassColor = vColor;
}