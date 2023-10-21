#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

void Triangle::Initialize(GLuint* shaderProgram)
{
	shader = shaderProgram;
	coor[0] = -1; coor[1] = 0; coor[2] = 0;
	coor[3] = 1; coor[4] = 0; coor[5] = 0;
	coor[6] = 0; coor[7] = 2; coor[8] = 0;

	scale_size = 1;
	rotate_rad = glm::vec3(0, 0, 0);
	trans_dis = glm::vec3(0, 0, 0);

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd_color(0.0, 1.0);

	for (int i = 0; i < 9; i += 3) {
		color[i] = urd_color(dre);
		color[i + 1] = urd_color(dre);
		color[i + 2] = urd_color(dre);
	}

	FinalTransformMatrix = glm::mat4(1.0f);
	transMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	first_rotate = glm::mat4(1.0f);

	glUseProgram(*shader);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO);

	GLuint loc = glGetAttribLocation(*shader, "vPos");

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(*shader, "vColor");

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);

	fold_size = -30;
	first_rotate = glm::rotate(first_rotate, glm::radians(-30.0f), glm::vec3(1, 0, 0));
	fold = true;
	state_r = false;
}

void Triangle::Draw()
{
	FinalTransformMatrix = transMatrix * rotateMatrix * first_rotate * scaleMatrix;
	unsigned int loc = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(FinalTransformMatrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::Update_rotate(float rad, float x, float y, float z)
{
	if (x > y && x > z)
		rotate_rad.x = rad;
	else if (y > x && y > z)
		rotate_rad.y = rad;
	else if (z > x && z > y)
		rotate_rad.z = rad;
	rotateMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rad), glm::vec3(x, y, z));
}

void Triangle::Update_scale(float size)
{
	scaleMatrix = glm::mat4(1.0f);
	scale_size = size;
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(scale_size, scale_size, scale_size));
}

void Triangle::Update_trans(float x, float y, float z)
{
	trans_dis = glm::vec3(x, y, z);
	transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, trans_dis);
}

void Triangle::change_bfold(bool flag)
{
	fold = flag;
}

void Triangle::fold_poly()
{
	if (not state_r) {
		if (fold) {
			if (fold_size > -30) {
				fold_size -= 10;
				first_rotate = glm::rotate(first_rotate, glm::radians(-10.0f), glm::vec3(1, 0, 0));
			}
		}
		else {
			if (fold_size < 210) {
				fold_size += 10;
				first_rotate = glm::rotate(first_rotate, glm::radians(10.0f), glm::vec3(1, 0, 0));
			}
		}
	}
	else {
		if (fold) {
			if (fold_size > -30) {
				fold_size -= 10;
				first_rotate = glm::rotate(first_rotate, glm::radians(-10.0f), glm::vec3(1, 0, 0));
			}
		}
		else {
			if (fold_size < 90) {
				fold_size += 10;
				first_rotate = glm::rotate(first_rotate, glm::radians(10.0f), glm::vec3(1, 0, 0));
			}
		}
	}
}

void Triangle::change_state(bool flag)
{
	state_r = flag;
}