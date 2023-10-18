#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Initialize(GLuint* shaderProgram)
{
	shader = shaderProgram;
	cameraPos = glm::vec3(1, 1, 1);
	cameraDirection = glm::vec3(0, 0, 0);
	cameraUp = glm::vec3(0, 1, 0);
	OuttoVS();
}

void Camera::Update_camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
{
	cameraPos = pos;
	cameraDirection = dir;
	cameraUp = up;
	OuttoVS();
}

void Camera::OuttoVS()
{
	view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int uni = glGetUniformLocation(*shader, "view");
	glUniformMatrix4fv(uni, 1, GL_FALSE, &view[0][0]);
}