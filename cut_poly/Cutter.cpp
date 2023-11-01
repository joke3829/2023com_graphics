#include "Cutter.h"

void Cutter::initialize(GLuint* shaderProgram)
{
	modelTrans = glm::mat4(1.0f);
	shader = shaderProgram;
	color[0] = color[3] = 1;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);
}

void Cutter::startPos(float x, float y)
{
	coor[0] = x; coor[1] = y;
}

void Cutter::endPos(float x, float y)
{
	coor[3] = x; coor[4] = y;
}

void Cutter::BufferUpdate()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
	unsigned int loc = glGetAttribLocation(*shader, "vPos");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	loc = glGetAttribLocation(*shader, "vColor");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);
}

void Cutter::Draw()
{
	BufferUpdate();
	unsigned int uni = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(modelTrans));
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
}

glm::vec2 Cutter::return_start()
{
	glm::vec2 srt(coor[0], coor[1]);
	return srt;
}

glm::vec2 Cutter::return_end()
{
	glm::vec2 ed(coor[3], coor[4]);
	return ed;
}