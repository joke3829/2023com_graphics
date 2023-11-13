
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

	cur_loc = glm::vec3(0, 0, 0);
	radius = 1;
	b_radius = 5;

	right = up = true;
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

void Mesh::setScale(float new_size)
{
	glm::mat4 temp(1.0f);
	modelTrans = glm::scale(temp, glm::vec3(new_size, new_size, new_size)) * modelTrans;
	b_radius = b_radius * new_size;
}

void Mesh::anime()
{
	glm::vec3 temp_loc;
	if (right && up) {
		temp_loc = cur_loc + glm::vec3(0.2, 0.4, 0);
	}
	else if (right && !up) {
		temp_loc = cur_loc + glm::vec3(0.2, -0.4, 0);
	}
	else if (!right && up) {
		temp_loc = cur_loc + glm::vec3(-0.2, 0.4, 0);
	}
	else if (!right && !up) {
		temp_loc = cur_loc + glm::vec3(-0.2, -0.4, 0);
	}
	Move(temp_loc);
}

void Mesh::Move(glm::vec3 new_loc)
{
	glm::mat4 temp(1.0f);
	modelTrans = glm::translate(temp, -cur_loc) * modelTrans;
	cur_loc = new_loc;
	temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, cur_loc) * modelTrans;
}

glm::vec3 Mesh::getCenter()
{
	return cur_loc;
}

float Mesh::getRadius(int n)
{
	if (n == 0)
		return radius;
	else
		return b_radius;
}

void Mesh::setRight(bool flag)
{
	right = flag;
}

void Mesh::setUp(bool flag)
{
	up = flag;
}

void Mesh::setCur_loc()
{
	glm::vec3 temp_loc;
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd(-8, 8);
	temp_loc = glm::vec3(urd(dre), urd(dre), 0);
	Move(temp_loc);
}

void Mesh::setCur_loc(glm::vec3 temp)
{
	Move(temp);
}

void Mesh::falling(int way)
{
	glm::vec3 temp_loc;
	switch (way) {
	case 8:
		temp_loc = cur_loc + glm::vec3(0, 0.1, 0);
		break;
	case 2:
		temp_loc = cur_loc + glm::vec3(0, -0.1, 0);
		break;
	}
	Move(temp_loc);
}

void Mesh::b_move(float wor_rot)
{
	glm::vec3 temp;
	temp = cur_loc - glm::vec3(1 * (wor_rot / 60), 0, 0);
	if (temp.x + b_radius >= 10)
		temp.x = 10 - b_radius;
	else if (temp.x - b_radius <= -10)
		temp.x = -10 + b_radius;
	Move(temp);
}