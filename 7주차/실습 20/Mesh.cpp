
#include "Mesh.h"

Mesh::Mesh() {
}

Mesh::~Mesh()
{
}

void Mesh::Initialize(GLuint* shaderprogram, std::string filename)
{
	if (not ReadOBJ(filename)) {
		std::cerr << "obj가 제대로 적용되지 않았습니다" << "\n";
		return;
	}
	// 현재는 랜덤하게 컬러 지정

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd_color(0.0, 1.0);

	for (int i = 0; i < vertexs.size(); ++i) {
		glm::vec3 temp_color;
		temp_color.x = urd_color(dre);
		temp_color.y = urd_color(dre);
		temp_color.z = urd_color(dre);
		colors.push_back(temp_color);
	}

	modelTrans = glm::mat4(1.0f);

	init_pos = glm::vec3(0, 0, 0);
	cur_loc = glm::vec3(0, 0, 0);
	init_rot = glm::vec3(0, 0, 0);
	cur_rot = glm::vec3(0, 0, 0);

	shader = shaderprogram;
	glUseProgram(*shader);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index.size(), &index.front(), GL_STATIC_DRAW);

	GLuint loc = glGetAttribLocation(*shader, "vPos");

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexs.size(), &vertexs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(*shader, "vColor");

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(), &colors.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

}
// 제대로 읽어 오면 true반환, 지금은 정점과 index만 저장, 추후 수정
bool Mesh::ReadOBJ(std::string filename)
{
	triangle_num = 0;
	char c;
	std::string str;
	std::ifstream fin(filename);
	if (not fin) {
		std::cerr << "obj파일을 찾지 못했습니다. " << "\n";
		return false;
	}
	std::stringstream stream;
	stream.str("");
	fin >> std::noskipws;
	while (not fin.eof()) {
		fin >> c;
		str += c;
		if (c == '\n') {
			if (str[0] == 'v' && str[1] == ' ') {
				stream.str(str);
				char novalue;
				glm::vec3 temp_vertex;
				stream >> novalue >> temp_vertex.x >> temp_vertex.y >> temp_vertex.z;
				vertexs.push_back(temp_vertex);
				stream.str("");
			}
			else if (str[0] == 'f' && str[1] == ' ') {
				stream.str(str);
				triangle_num++;
				char type;
				int novalue;
				int temp_index[3];
				int real_index[3];
				stream >> type >> temp_index[0] >> type >> novalue >> type >> novalue
					>> temp_index[1] >> type >> novalue >> type >> novalue 
					>> temp_index[2] >> type >> novalue >> type >> novalue;
				for (int i = 0; i < 3; ++i) {
					real_index[i] = temp_index[i] - 1;
				}
				index.push_back(real_index[0]);
				index.push_back(real_index[1]);
				index.push_back(real_index[2]);
				stream.str("");
			}
			str = "";
		}
	}
	return true;
}

void Mesh::Draw()
{
	unsigned int loc = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelTrans));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3 * triangle_num, GL_UNSIGNED_INT, 0);
}

void Mesh::init_scale(float size)
{
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::scale(temp, glm::vec3(size, size, size)) * modelTrans;
}

void Mesh::init_position(float x, float y, float z)
{
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(x, y, z)) * modelTrans;
	init_pos = glm::vec3(x, y, z);
}

void Mesh::init_rotate(float rad, float x, float y, float z)
{
	if (x > y && x > z)
		init_rot.x += rad;
	else if (y > x && y > z)
		init_rot.y += rad;
	else if (z > x && z > y)
		init_rot.z += rad;
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(rad), glm::vec3(x, y, z)) * modelTrans;
}

void Mesh::Move(glm::vec3 new_loc)
{
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(-cur_loc.x, -cur_loc.y, -cur_loc.z)) * modelTrans;
	cur_loc = new_loc;
	modelTrans = glm::translate(temp, glm::vec3(cur_loc.x, cur_loc.y, cur_loc.z)) * modelTrans;
}

void Mesh::Rotate(glm::vec3 new_rot)
{
	glm::mat4 temp = glm::mat4(1.0f);
	/*modelTrans = glm::translate(temp, glm::vec3(-init_pos.x, -init_pos.y, -init_pos.z)) * modelTrans;
	temp = glm::mat4(1.0f);*/
	modelTrans = glm::translate(temp, glm::vec3(-cur_loc.x, -cur_loc.y, -cur_loc.z)) * modelTrans;
	temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(-cur_rot.x), glm::vec3(0, 1, 0)) * modelTrans;
	cur_rot = new_rot;
	temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(cur_rot.x), glm::vec3(0, 1, 0)) * modelTrans;
	/*temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(init_pos.x, init_pos.y, init_pos.z)) * modelTrans;*/
	temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(cur_loc.x, cur_loc.y, cur_loc.z)) * modelTrans;
}


void Mesh::front_rot(int way)
{
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(-cur_loc.x, -cur_loc.y, -cur_loc.z)) * modelTrans;
	switch (way) {
	case 4:
		temp = glm::mat4(1.0f);
		modelTrans = glm::rotate(temp, glm::radians(5.0f), glm::vec3(0, 1, 0)) * modelTrans;
		break;
	case 6:
		temp = glm::mat4(1.0f);
		modelTrans = glm::rotate(temp, glm::radians(-5.0f), glm::vec3(0, 1, 0)) * modelTrans;
		break;
	}
	temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(cur_loc.x, cur_loc.y, cur_loc.z)) * modelTrans;
}

void Mesh::front_merge(int way)
{
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(-cur_rot.x), glm::vec3(0, 1, 0)) * modelTrans;
	temp = glm::mat4(1.0f);
	switch (way) {
	case 4:
		modelTrans = glm::translate(temp, glm::vec3(-init_pos.x, 0, 0)) * modelTrans;
		init_pos.x += 0.1;
		temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(init_pos.x, 0, 0)) * modelTrans;
		break;
	case 6:
		modelTrans = glm::translate(temp, glm::vec3(-init_pos.x, 0, 0)) * modelTrans;
		init_pos.x -= 0.1;
		temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(init_pos.x, 0, 0)) * modelTrans;
		break;
	}
	temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(cur_rot.x), glm::vec3(0, 1, 0)) * modelTrans;
	
}

void Mesh::raider_rot(int way)
{
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(-cur_loc.x, -cur_loc.y, -cur_loc.z)) * modelTrans;
	temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(-init_pos.x, -init_pos.y, -init_pos.z))* modelTrans;
	temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(-cur_rot.x), glm::vec3(0, 1, 0)) * modelTrans;
	temp = glm::mat4(1.0f);
	switch (way) {
	case 4:
		modelTrans = glm::rotate(temp, glm::radians(-5.0f), glm::vec3(1, 0, 0)) * modelTrans;
		break;
	case 6:
		modelTrans = glm::rotate(temp, glm::radians(5.0f), glm::vec3(1, 0, 0)) * modelTrans;
		break;
	}
	temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(cur_rot.x), glm::vec3(0, 1, 0)) * modelTrans;
	temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(cur_loc.x, cur_loc.y, cur_loc.z)) * modelTrans;
	temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(init_pos.x, init_pos.y, init_pos.z)) * modelTrans;
}