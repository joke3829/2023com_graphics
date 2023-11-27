#pragma once
#include "stdafx.h"

class Sier {
public:
	void Initialize(GLuint*, int w);
	void sierpinski(glm::vec3, glm::vec3, glm::vec3, int d);
	void DrawTriangle(glm::vec3, glm::vec3, glm::vec3);
private:
	GLuint* shader;
	GLuint VAO, VBO[3];
	int depth;
	int way;
};