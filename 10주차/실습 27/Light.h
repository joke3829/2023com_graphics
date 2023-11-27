#pragma once

#include "stdafx.h"

class LightObject {
public:
	void Initialize(GLuint*);
	void rotate(int);
	void OutToVS();
private:
	float dis;
	glm::vec2 angle;
	GLuint* shader;
	glm::vec3 lightColor;
	glm::vec3 lightPos;
};