#pragma once
#include "stdafx.h"

class Camera {
	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::mat4 view;
	glm::vec2 rotation_angle;
	float camera_dis;

	GLuint* shader;
public:
	Camera();
	~Camera();
	void Initialize(GLuint*);
	void Update_camera(glm::vec3, glm::vec3, glm::vec3);
	void OuttoVS();
	void y_rotate_timer();
};