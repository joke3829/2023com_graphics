#include "Wall.h"

void Wall::Initialize(GLuint* shaderProgram, float r, float g, float b, int type)
{
	door_num = type;
	shader = shaderProgram;
	if (type == 0) {
		coor[0] = -10; coor[1] = 10;
		coor[3] = -10; coor[4] = -10;
		coor[6] = 10; coor[7] = -10;
		coor[9] = 10; coor[10] = 10;
	}
	else if (type == 1 || type == 2) {
		coor[0] = -5; coor[1] = 10;
		coor[3] = -5; coor[4] = -10;
		coor[6] = 5; coor[7] = -10;
		coor[9] = 5; coor[10] = 10;
	}

	color[0] = color[3] = color[6] = color[9] = r;
	color[1] = color[4] = color[7] = color[10] = g;
	color[2] = color[5] = color[8] = color[11] = b;

	center = glm::vec3(0, 0, 0);
	rotation_angle = 0;

	modelTrans = glm::mat4(1.0f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);

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

void Wall::Draw()
{
	int uni = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(modelTrans));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Wall::Rotate(float rad, glm::vec3 axis)
{
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(rad), axis) * modelTrans;
}

void Wall::Move(glm::vec3 new_loc)
{
	center = new_loc;
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, center) * modelTrans;
}

void Wall::Open(int way) {
	glm::mat4 temp = glm::mat4(1.0f);
	if (door_num == 1) {		//¿ÞÂÊ ¹®
		modelTrans = glm::translate(temp, -center) * modelTrans; temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(5, 0, 0)) * modelTrans; temp = glm::mat4(1.0f);
		switch (way) {
		case 4:	// ¿­¸²
			if (rotation_angle < 100) {
				rotation_angle += 5;
				modelTrans = glm::rotate(temp, glm::radians(-5.0f), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);

			}
			break;
		case 6: // ´ÝÈû
			if (rotation_angle > 0) {
				rotation_angle -= 5;
				modelTrans = glm::rotate(temp, glm::radians(5.0f), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);
			}
			break;
		}
		modelTrans = glm::translate(temp, center) * modelTrans; temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(-5, 0, 0)) * modelTrans; temp = glm::mat4(1.0f);
	}
	else if (door_num == 2) {	// ¿À¸¥ÂÊ¹®
		modelTrans = glm::translate(temp, -center) * modelTrans; temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(-5, 0, 0)) * modelTrans; temp = glm::mat4(1.0f);
		switch (way) {
		case 4:	// ¿­¸²
			if (rotation_angle < 100) {
				rotation_angle += 5;
				modelTrans = glm::rotate(temp, glm::radians(5.0f), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);

			}
			break;
		case 6: // ´ÝÈû
			if (rotation_angle > 0) {
				rotation_angle -= 5;
				modelTrans = glm::rotate(temp, glm::radians(-5.0f), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);
			}
			break;
		}
		modelTrans = glm::translate(temp, center) * modelTrans; temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(5, 0, 0)) * modelTrans; temp = glm::mat4(1.0f);
	}
}

bool Wall::crash_check(const Robot& t_robot)
{
	return true;
}
