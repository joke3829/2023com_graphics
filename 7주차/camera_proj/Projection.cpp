#include "Projection.h"

Projection::Projection()
{
}

Projection::~Projection()
{
}

void Projection::Initialize(GLuint* shaderProgram)
{
	shader = shaderProgram;
	fovy = 45;
	aspect = 1;
	n = 0.1;
	f = 50;
	OuttoVS();
}

void Projection::Update_Proj(float temp_fov, float temp_aspect, float temp_n, float temp_f)
{
	fovy = temp_fov;
	aspect = temp_aspect;
	n = temp_n;
	f = temp_f;
	OuttoVS();
}

void Projection::OuttoVS()
{
	proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(fovy), aspect, n, f);
	unsigned int uni = glGetUniformLocation(*shader, "proj");
	glUniformMatrix4fv(uni, 1, GL_FALSE, &proj[0][0]);
}