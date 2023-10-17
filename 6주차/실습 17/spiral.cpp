#include "spiral.h"

spiral::spiral()
{
}

spiral::~spiral()
{
}

void spiral::Initialize(GLuint* shaderProgram, int arrow)
{
	shader = shaderProgram;
	FinalTransformMatrix = glm::mat4(1.0f);
	finalrotate = glm::mat4(1.0f);
	finalrotate = glm::rotate(finalrotate, glm::radians(45.0f), glm::vec3(1, 0, 0));
	rotateMatrix = glm::mat4(1.0f);
	//rotateMatrix = glm::rotate(rotateMatrix, glm::radians(-50.0f), glm::vec3(0, 1, 0));
	float r1 = 0.0;
	int rad = 0;
	color[0] = 0;
	color[1] = 1;
	color[2] = 0;
	switch (arrow) {
	case 0:
		for (int i = 0; i < 600; i += 3) {
			coor[i] = r1 * cos((M_PI/ 20) * rad);
			coor[i + 1] = r1 * sin((M_PI / 20) * rad);

			rad += 1;
			r1 += 0.005;

			color[i] = 0;
			color[i + 1] = 1;
			color[i + 2] = 0;
		}
		break;
	case 1:
		for (int i = 0; i < 600; i += 3) {
			coor[i] = r1 * glm::cos(M_PI / 20 * rad);
			coor[i + 1] = r1 * glm::sin(M_PI / 20 * rad);

			rad += 1;
			r1 -= 0.005;

			color[i] = 0;
			color[i + 1] = 1;
			color[i + 2] = 0;
		}
		break;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	unsigned int loc = glGetAttribLocation(*shader, "vPos");
	glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), 0);
	glEnableVertexAttribArray(loc);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	loc = glGetAttribLocation(*shader, "vColor");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);
}

void spiral::Draw()
{
	FinalTransformMatrix = finalrotate * rotateMatrix;
	unsigned int uni = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(FinalTransformMatrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 200);
}