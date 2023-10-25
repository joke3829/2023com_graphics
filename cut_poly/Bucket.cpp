
#include "Bucket.h"

void Bucket::Initialize(GLuint* shaderProgram)
{
	move_left = true;
	shader = shaderProgram;
	width = 0.4; height = 0.1;
	left_b = glm::vec2(-0.2, -0.9);
	coor[0] = left_b.x; coor[1] = left_b.y + height;
	coor[3] = left_b.x; coor[4] = left_b.y;
	coor[6] = left_b.x + width; coor[7] = left_b.y;
	coor[9] = left_b.x + width; coor[10] = left_b.y + height;

	color[2] = color[5] = color[8] = color[11] = 1;

	modelTrans = glm::mat4(1.0f);

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
}

void Bucket::Move()
{
	glm::mat4 temp = glm::mat4(1.0f);
	if (move_left) {
		modelTrans = glm::translate(temp, glm::vec3(-left_b.x, -left_b.y, 0)) * modelTrans;
		left_b.x -= 0.01;
		temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(left_b.x, left_b.y, 0)) * modelTrans;
		if (left_b.x <= -1)
			move_left = false;
	}
	else {
		modelTrans = glm::translate(temp, glm::vec3(-left_b.x, -left_b.y, 0)) * modelTrans;
		left_b.x += 0.01;
		temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(left_b.x, left_b.y, 0)) * modelTrans;
		if (left_b.x + width >= 1)
			move_left = true;
	}
}

void Bucket::Draw()
{
	unsigned int uni = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(modelTrans));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}