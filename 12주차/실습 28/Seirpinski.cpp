#include "Sierpinski.h"

void Sier::Initialize(GLuint* shaderprogram, int w)
{
	shader = shaderprogram;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	depth = 0;
	way = w;
}

void Sier::sierpinski(glm::vec3 pos_1, glm::vec3 pos_2, glm::vec3 pos_3, int d)
{
	if (d == 0) {
		DrawTriangle(pos_1, pos_2, pos_3);
	}
	else {
		glm::vec3 mid1(((pos_1.x + pos_2.x) / 2), ((pos_1.y + pos_2.y) / 2), ((pos_1.z + pos_2.z) / 2));
		glm::vec3 mid2(((pos_2.x + pos_3.x) / 2), ((pos_2.y + pos_3.y) / 2), ((pos_2.z + pos_3.z) / 2));
		glm::vec3 mid3(((pos_1.x + pos_3.x) / 2), ((pos_1.y + pos_3.y) / 2), ((pos_1.z + pos_3.z) / 2));

		sierpinski(pos_1, mid1, mid3, d - 1);
		sierpinski(mid1, pos_2, mid2, d - 1);
		sierpinski(mid3, mid2, pos_3, d - 1);
	}
}


void Sier::DrawTriangle(glm::vec3 pos_1, glm::vec3 pos_2, glm::vec3 pos_3)
{
	std::vector<glm::vec3> t_pos;
	t_pos.push_back(pos_1);
	t_pos.push_back(pos_2);
	t_pos.push_back(pos_3);
	std::vector<glm::vec3> t_color;
	for (int i = 0; i < 3; ++i)
		t_color.push_back(glm::vec3(0, 1, 1));
	glUseProgram(*shader);
	glBindVertexArray(VAO);

	GLuint loc = glGetAttribLocation(*shader, "vPos");
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * t_pos.size(), &t_pos.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(*shader, "vColor");
	// 컬러
	//std::cout << loc << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * t_color.size(), &t_color.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);


	loc = glGetAttribLocation(*shader, "vNormal");
	std::vector<glm::vec3> t_normal;
	switch (way) {
	case 0:	// 좌
		for (int i = 0; i < 3; ++i) 
			t_normal.push_back(glm::vec3(-1, 0, 0));
		break;
	case 1: // 앞
		for (int i = 0; i < 3; ++i)
			t_normal.push_back(glm::vec3(0, 0, 1));
		break;
	case 2: // 우
		for (int i = 0; i < 3; ++i)
			t_normal.push_back(glm::vec3(1, 0, 0));
		break;
	case 3:	// 뒤
		for (int i = 0; i < 3; ++i)
			t_normal.push_back(glm::vec3(0, 0, -1));
		break;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * t_normal.size(), &t_normal.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}