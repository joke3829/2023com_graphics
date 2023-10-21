#include "ortho.h"

void Ortho::Initialize(GLuint* shaderProgram)
{
	shader = shaderProgram;
	proj = glm::mat4(1.0f);

	proj = glm::ortho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
	//proj = glm::translate(proj, glm::vec3(0, 0, -3));
}

void Ortho::OuttoVS()
{
	unsigned int loc = glGetUniformLocation(*shader, "proj");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &proj[0][0]);
}