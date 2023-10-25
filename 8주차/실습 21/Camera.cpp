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
	camera_dis = 40;
	//rotation_angle = glm::vec2(30, 30);
	rotation_angle = glm::vec2(-45, 30);
	cameraDirection = glm::vec3(0, 0, 0);
	cameraUp = glm::vec3(0, 1, 0);
	OuttoVS();
}

void Camera::Control_camera(glm::vec3 loc, glm::vec3 angle)
{
	cameraDirection = loc;
	rotation_angle.x = -angle.x - 90;
	rotation_angle.y = 20;
	camera_dis = 10;
	OuttoVS();
}

void Camera::Control_init()
{
	rotation_angle = glm::vec2(-45, 30);
	cameraDirection = glm::vec3(0, 0, 0);
	camera_dis = 15;
	OuttoVS();
}

void Camera::OuttoVS()
{
	float xz_dis;
	xz_dis = fabs(camera_dis * glm::cos(glm::radians(rotation_angle.y)));
	cameraPos.x = cameraDirection.x + (xz_dis * glm::cos(glm::radians(rotation_angle.x)));
	cameraPos.y = cameraDirection.y + (camera_dis * glm::sin(glm::radians(rotation_angle.y)));
	cameraPos.z = cameraDirection.z + (xz_dis * glm::sin(glm::radians(rotation_angle.x)));
	view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int uni = glGetUniformLocation(*shader, "view");
	glUniformMatrix4fv(uni, 1, GL_FALSE, &view[0][0]);
}

void Camera::Vertical_Move(int way)			// 수직 이동
{
	switch (way) {
	case 8:
		cameraPos.y += 0.5;
		cameraDirection.y += 0.5;
		break;
	case 2:
		cameraPos.y -= 0.5;
		cameraDirection.y -= 0.5;
		break;
	}
	OuttoVS();
}

void Camera::Direcion_Move(int way)			// 시점 이동
{
	float xz_dis;
	switch (way) {
	case 8:
		rotation_angle.y -= 5;
		if (rotation_angle.y <= -90)
			rotation_angle.y = -90;
		cameraDirection.y = cameraPos.y + (camera_dis * glm::sin(glm::radians(-rotation_angle.y)));
		xz_dis = fabs(camera_dis * glm::cos(glm::radians(rotation_angle.y)));
		cameraDirection.x = cameraPos.x + (xz_dis * glm::cos(glm::radians(180 + rotation_angle.x)));
		cameraDirection.z = cameraPos.z + (xz_dis * glm::sin(glm::radians(180 + rotation_angle.x)));
		break;
	case 4:
		rotation_angle.x -= 5;
		if (rotation_angle.x <= -360)
			rotation_angle.x = 0;
		cameraDirection.y = cameraPos.y + (camera_dis * glm::sin(glm::radians(-rotation_angle.y)));
		xz_dis = fabs(camera_dis * glm::cos(glm::radians(rotation_angle.y)));
		cameraDirection.x = cameraPos.x + (xz_dis * glm::cos(glm::radians(180 + rotation_angle.x)));
		cameraDirection.z = cameraPos.z + (xz_dis * glm::sin(glm::radians(180 + rotation_angle.x)));
		break;
	case 2:
		rotation_angle.y += 5;
		if (rotation_angle.y >= 90)
			rotation_angle.y = 90;
		cameraDirection.y = cameraPos.y + (camera_dis * glm::sin(glm::radians(-rotation_angle.y)));
		xz_dis = fabs(camera_dis * glm::cos(glm::radians(rotation_angle.y)));
		cameraDirection.x = cameraPos.x + (xz_dis * glm::cos(glm::radians(180 + rotation_angle.x)));
		cameraDirection.z = cameraPos.z + (xz_dis * glm::sin(glm::radians(180 + rotation_angle.x)));
		break;
	case 6:
		rotation_angle.x += 5;
		if (rotation_angle.x >= 360)
			rotation_angle.x = 0;
		cameraDirection.y = cameraPos.y + (camera_dis * glm::sin(glm::radians(-rotation_angle.y)));
		xz_dis = fabs(camera_dis * glm::cos(glm::radians(rotation_angle.y)));
		cameraDirection.x = cameraPos.x + (xz_dis * glm::cos(glm::radians(180 + rotation_angle.x)));
		cameraDirection.z = cameraPos.z + (xz_dis * glm::sin(glm::radians(180 + rotation_angle.x)));
		break;
	}
	OuttoVS();
}

void Camera::Move(int way)				// 카메라 시선에 따른 이동
{
	glm::vec3 normal;
	glm::vec3 right;
	normal = glm::normalize(glm::vec3(cameraDirection.x - cameraPos.x, cameraDirection.y - cameraPos.y, cameraDirection.z - cameraPos.z));
	right = glm::normalize(glm::cross(normal, glm::vec3(0, 1, 0)));
	switch (way) {
	case 8:
		cameraDirection.x += normal.x; cameraDirection.y += normal.y; cameraDirection.z += normal.z;
		break;
	case 4:
		cameraDirection.x -= right.x; cameraDirection.y -= right.y; cameraDirection.z -= right.z;
		break;
	case 6:
		cameraDirection.x += right.x; cameraDirection.y += right.y; cameraDirection.z += right.z;
		break;
	case 2:
		cameraDirection.x -= normal.x; cameraDirection.y -= normal.y; cameraDirection.z -= normal.z;
		break;
	}
	OuttoVS();
}

void Camera::UpdateCamera(float x, float y, float dis)
{
	rotation_angle.x = x;
	rotation_angle.y = y;
	camera_dis = dis;
}

void Camera::Pos_update(glm::vec3 pos)
{
	cameraDirection = pos;
	camera_dis = sqrt((cameraPos.x - cameraDirection.x) * (cameraPos.x - cameraDirection.x) +
		(cameraPos.y - cameraDirection.y) * (cameraPos.y - cameraDirection.y) +
		(cameraPos.z - cameraDirection.z) * (cameraPos.z - cameraDirection.z));
}