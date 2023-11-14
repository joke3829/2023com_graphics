#include "Light.h"

void LightObject::Initialize(GLuint* shaderProgram)
{
	dis = 50;
	shader = shaderProgram;
	angle = glm::vec2(90, 0);
	lightColor = glm::vec3(1.0f);
	lightPos = glm::vec3(dis * glm::cos(glm::radians(angle.x)), 0, dis * glm::sin(glm::radians(angle.x)));
	OutToVS();
}

void LightObject::OutToVS()
{
	int uni = glGetUniformLocation(*shader, "lightColor");
	glUniform3f(uni, lightColor.x, lightColor.y, lightColor.z);
	uni = glGetUniformLocation(*shader, "lightPos");
	glUniform3f(uni, lightPos.x, lightPos.y, lightPos.z);
}

void LightObject::rotate(int way)
{
	switch (way) {
	case 4:
		angle.x += 5;
		break;
	case 6:
		angle.x -= 5;
		break;
	}
	lightPos = glm::vec3(dis * glm::cos(glm::radians(angle.x)), 0, dis * glm::sin(glm::radians(angle.x)));
	OutToVS();
}