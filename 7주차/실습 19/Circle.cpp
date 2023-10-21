#include "Circle.h"

Move_Circle::Move_Circle()
{}

Move_Circle::~Move_Circle()
{}

void Move_Circle::Initialize(GLuint* shaderProgram, float r)
{
	shader = shaderProgram;
	float rad = 0.0;
	for (int i = 0; i < 1080; i += 3) {
		coor[i] = r * glm::cos(glm::radians(rad));
		coor[i + 2] = r * glm::sin(glm::radians(rad));
		color[i] = 0; color[i + 1] = 0; color[i + 2] = 0;
		rad += 1;
	}
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);

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

	modelTrans = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);
	finalMat = glm::mat4(1.0f);

	move_dis = glm::vec3(0, 0, 0);
}

void Move_Circle::Draw()
{
	finalMat = rotateMatrix * modelTrans;
	unsigned int uni = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 360);
}

void Move_Circle::Move(float x, float y, float z)
{
	glm::mat4 calcu = glm::mat4(1.0f);
	modelTrans = glm::translate(calcu, glm::vec3(-move_dis.x, -move_dis.y, -move_dis.z)) * modelTrans;
	calcu = glm::mat4(1.0f);
	move_dis = glm::vec3(x, y, z);
	modelTrans = glm::translate(calcu, glm::vec3(move_dis.x, move_dis.y, move_dis.z)) * modelTrans;
}

void Move_Circle::decide(glm::mat4 temp)
{
	rotateMatrix = temp;
}

void Move_Circle::decide(float rr, float x, float y, float z)
{
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rr), glm::vec3(x, y, z));
}