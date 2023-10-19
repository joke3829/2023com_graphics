
#include "Line.h"

Mesh::Mesh() {
}

Mesh::~Mesh()
{
}

void Mesh::Initialize(GLuint* shaderprogram)
{
	// 현재는 랜덤하게 컬러 지정
	scale_size = 1;
	rotate_rad = glm::vec3(0, 0, 0);
	trans_dis = glm::vec3(0, 0, 0);

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd_color(0.0, 1.0);

	for (int i = 0; i < 12; i += 3) {
		color[i] = urd_color(dre);
		color[i + 1] = urd_color(dre);
		color[i + 2] = urd_color(dre);
	}

	coor[0] = -1; coor[1] = -1; coor[2] = 0;		// 0
	coor[3] = 1; coor[4] = -1; coor[5] = 0;			// 1
	coor[6] = 1; coor[7] = 1; coor[8] = 0;			// 2
	coor[9] = -1; coor[10] = 1; coor[11] = 0;		// 3

	index[0] = 0; index[1] = 1; index[2] = 3;
	index[3] = 1; index[4] = 2; index[5] = 3;

	FinalTransformMatrix = glm::mat4(1.0f);
	transMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	firsttransMatrix = glm::mat4(1.0f);

	shader = shaderprogram;
	glUseProgram(*shader);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	GLuint loc = glGetAttribLocation(*shader, "vPos");

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(*shader, "vColor");

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glEnableVertexAttribArray(loc);

}
// 제대로 읽어 오면 true반환, 지금은 정점과 index만 저장, 추후 수정
void Mesh::Draw()
{
	FinalTransformMatrix = transMatrix * rotateMatrix * firsttransMatrix * scaleMatrix;
	unsigned int loc = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(FinalTransformMatrix));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::Update_rotate(float rad, float x, float y, float z)
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

void Mesh::Update_scale(float size)
{
	scaleMatrix = glm::mat4(1.0f);
	scale_size = size;
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(scale_size, scale_size, scale_size));
}

void Mesh::Update_trans(float x, float y, float z)
{
	trans_dis = glm::vec3(x, y, z);
	transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, trans_dis);
}

void Mesh::Update_first()	//앞면만 적용
{
	firsttransMatrix = glm::translate(firsttransMatrix, glm::vec3(0, 1.5, 0));
}

void Mesh::t_rotate()
{
	rotate_rad.x += 10;
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0));
}

void Mesh::f_rotate(bool flag)
{
	if (flag) {
		if (rotate_rad.x < 90) {
			rotate_rad.x += 10.0;
			rotateMatrix = glm::rotate(rotateMatrix, glm::radians(10.0f), glm::vec3(1, 0, 0));
		}
	}
	else {
		if (rotate_rad.x > 0) {
			rotate_rad.x -= 10.0;
			rotateMatrix = glm::rotate(rotateMatrix, glm::radians(-10.0f), glm::vec3(1, 0, 0));
		}
	}
}

void Mesh::s_move(bool flag)
{
	if (flag) {
		if (trans_dis.y < 3) {
			trans_dis.y += 0.5;
			transMatrix = glm::translate(transMatrix, glm::vec3(0, 0.5, 0));
		}
	}
	else {
		if (trans_dis.y > 0) {
			trans_dis.y -= 0.5;
			transMatrix = glm::translate(transMatrix, glm::vec3(0, -0.5, 0));
		}
	}
}

void Mesh::b_scale(bool flag)
{
	if (flag) {
		if (scale_size > 0) {
			scale_size -= 0.1;
			scaleMatrix = glm::mat4(1.0f);
			scaleMatrix = glm::scale(scaleMatrix, glm::vec3(scale_size, scale_size, scale_size));
		}
	}
	else {
		if (scale_size < 1.5) {
			scale_size += 0.1;
			scaleMatrix = glm::mat4(1.0f);
			scaleMatrix = glm::scale(scaleMatrix, glm::vec3(scale_size, scale_size, scale_size));
		}
	}
}