#pragma once
#include "Mesh.h"

class Line {
	float coor[6];
	float color[6];
	GLuint vao, vbo[2];
	glm::mat4 trans;
	GLuint* shader;
public:
	Line(int);
	~Line();
	void Initialize(GLuint*);
	void Draw();
};