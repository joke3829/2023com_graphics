#include "Line.h"

Line::Line(int x)
{
	switch (x) {
	case 0:
		coor[0] = -1; coor[1] = 0; coor[2] = 0;
		coor[3] = 1; coor[4] = 0; coor[5] = 0;
		color[0] = 1; color[1] = 0; color[2] = 0;
		color[3] = 1; color[4] = 0; color[5] = 0;
		break;
	case 1:
		coor[0] = 0; coor[1] = -1; coor[2] = 0;
		coor[3] = 0; coor[4] = 1; coor[5] = 0;
		color[0] = 0; color[1] = 1; color[2] = 0;
		color[3] = 0; color[4] = 1; color[5] = 0;
		break;
	}
}

Line::~Line()
{
}

void Line::Initialize(GLuint* shaderprogram)
{
	shader = shaderprogram;
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
	unsigned int loc = glGetAttribLocation(*shader, "vPos");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	loc = glGetAttribLocation(*shader, "vColor");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	trans = glm::mat4(1.0f);
}

void Line::Draw()
{
	unsigned int uni = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(trans));
	glBindVertexArray(vao);

	glDrawArrays(GL_LINES, 0, 2);
}