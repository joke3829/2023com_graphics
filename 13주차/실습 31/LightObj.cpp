#include "LightObj.h"
#include "ShaderProgram.h"

LightObj::LightObj()
{
	shader = ShaderProgram::getShader();
	lightColor = glm::vec3(1.0, 1.0, 1.0);
	OutToShader();
}


void LightObj::lightButton()
{
	if (lightColor == glm::vec3(0.0, 0, 0))
		lightColor = glm::vec3(1, 1, 1);
	else
		lightColor = glm::vec3(0, 0, 0);

	OutToShader();
}

void LightObj::change_color(int n)
{
	switch (n) {
	case 7:
		lightColor = glm::vec3(1, 0.01, 0.01);
		break;
	case 8:
		lightColor = glm::vec3(0.01, 1, 0.01);
		break;
	case 9:
		lightColor = glm::vec3(0.01, 0.01, 1);
		break;
	}
	OutToShader();
}

void LightObj::OutToShader()
{
	int uni = glGetUniformLocation(shader->s_program, "lightColor");
	glUniform3fv(uni, 1, glm::value_ptr(lightColor));
}