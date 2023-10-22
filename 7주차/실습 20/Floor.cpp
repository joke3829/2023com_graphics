#include "Floor.h"

void Floor::Initialize(GLuint* shaderProgram)
{

	modelTrans = glm::mat4(1.0f);

	coor[0] = -30; coor[1] = 0; coor[2] = 30;
	coor[3] = 30; coor[4] = 0; coor[5] = 30;
	coor[6] = 30; coor[7] = 0; coor[8] = -30;
	coor[9] = -30; coor[10] = 0; coor[11] = -30;

	color[0] = 0; color[1] = 0; color[2] = 0;
	color[3] = 0; color[4] = 1; color[5] = 0;
	color[6] = 1; color[7] = 1; color[8] = 1;
	color[9] = 0; color[10] = 1; color[11] = 0;

	shader = shaderProgram;
	glUseProgram(*shader);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO);

	GLuint loc = glGetAttribLocation(*shader, "vPos");

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(*shader, "vColor");

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

}

void Floor::Draw()
{
	unsigned int loc = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelTrans));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}