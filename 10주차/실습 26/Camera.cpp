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
	camera_dis = 100;
	rotation_angle = glm::vec2(90, 0);
	cameraPos.x = cameraDirection.x + (camera_dis * glm::cos(glm::radians(rotation_angle.x)));
	cameraPos.y = cameraDirection.y + (camera_dis * glm::sin(glm::radians(rotation_angle.y)));
	cameraPos.z = cameraDirection.z + (camera_dis * glm::sin(glm::radians(rotation_angle.x)));
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
	uni = glGetUniformLocation(*shader, "viewPos");
	glUniform3f(uni, cameraPos.x, cameraPos.y, cameraPos.z);
}

void Camera::y_rotate_timer()
{
	rotation_angle.x += 5;
	if (rotation_angle.x >= 360)
		rotation_angle.x = 0;
	cameraPos.x = cameraDirection.x + (camera_dis * glm::cos(glm::radians(rotation_angle.x)));
	cameraPos.y = cameraDirection.y + (camera_dis * glm::sin(glm::radians(rotation_angle.y)));
	cameraPos.z = cameraDirection.z + (camera_dis * glm::sin(glm::radians(rotation_angle.x)));
	OuttoVS();
}