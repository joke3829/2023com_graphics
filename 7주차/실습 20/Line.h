#pragma once
#include "Crane.h"

class Line {
	float coor[6];
	float color[6];
	GLuint vao, vbo[2];
	glm::mat4 scale;
	glm::mat4 trans;
	float scale_size;
	GLuint* shader;
public:
	Line(int);
	~Line();
	void Initialize(GLuint*);
	void Update_scale(float);
	void Draw();
};