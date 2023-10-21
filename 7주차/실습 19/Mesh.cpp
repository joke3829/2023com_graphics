
#include "Mesh.h"

Mesh::Mesh() {
}

Mesh::~Mesh()
{
}

void Mesh::Initialize(GLuint* shaderprogram, std::string filename, float s_size, float r)
{
	if (not ReadOBJ(filename)) {
		std::cerr << "obj가 제대로 적용되지 않았습니다" << "\n";
		return;
	}
	// 현재는 랜덤하게 컬러 지정

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd_color(0.0, 1.0);
	std::uniform_real_distribution<float> urd_speed(1.0, 5.0);

	for (int i = 0; i < vertexs.size(); ++i) {
		glm::vec3 temp_color;
		temp_color.x = urd_color(dre);
		temp_color.y = urd_color(dre);
		temp_color.z = urd_color(dre);
		colors.push_back(temp_color);
	}
	speed = urd_speed(dre);
	finalMatrix = glm::mat4(1.0f);
	modelTrans = glm::mat4(1.0f);
	rotate_world = glm::mat4(1.0f);
	move_dis = glm::vec3(0, 0, 0);
	calculate_mat = glm::mat4(1.0f);
	rotate_rad = 0;
	
	modelTrans = glm::scale(calculate_mat, glm::vec3(s_size, s_size, s_size)) * modelTrans;
	calculate_mat = glm::mat4(1.0f);
	modelTrans = glm::translate(calculate_mat, glm::vec3(r, 0, 0)) * modelTrans;

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

	solid = true;
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
	finalMatrix = rotate_world *  modelTrans;
	unsigned int loc = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(finalMatrix));
	glBindVertexArray(VAO);
	if(solid)
		glDrawElements(GL_TRIANGLES, 3 * triangle_num, GL_UNSIGNED_INT, 0);
	else
		glDrawElements(GL_LINE_LOOP, 3 * triangle_num, GL_UNSIGNED_INT, 0);
}

void Mesh::Scale(float size)
{
	calculate_mat = glm::mat4(1.0f);
	modelTrans = glm::translate(calculate_mat, glm::vec3(-move_dis.x, -move_dis.y, -move_dis.z)) * modelTrans;
	calculate_mat = glm::mat4(1.0f);
	modelTrans = glm::scale(calculate_mat, glm::vec3(size, size, size)) * modelTrans;
	calculate_mat = glm::mat4(1.0f);
	modelTrans = glm::translate(calculate_mat, glm::vec3(move_dis.x, move_dis.y, move_dis.z)) * modelTrans;
}


void Mesh::Move(float x, float y, float z)
{
	calculate_mat = glm::mat4(1.0f);
	modelTrans = glm::translate(calculate_mat, glm::vec3(-move_dis.x, -move_dis.y, -move_dis.z)) * modelTrans;
	move_dis = glm::vec3(x, y, z);
	calculate_mat = glm::mat4(1.0f);
	modelTrans = glm::translate(calculate_mat, glm::vec3(move_dis.x, move_dis.y, move_dis.z)) * modelTrans;
}

void Mesh::Rotate_world()
{
	calculate_mat = glm::mat4(1.0f);
	modelTrans = glm::translate(calculate_mat, glm::vec3(-move_dis.x, -move_dis.y, -move_dis.z)) * modelTrans;
	calculate_mat = glm::mat4(1.0f);
	modelTrans = glm::rotate(calculate_mat, glm::radians(speed), glm::vec3(0, 1, 0)) * modelTrans;
	calculate_mat = glm::mat4(1.0f);
	modelTrans = glm::translate(calculate_mat, glm::vec3(move_dis.x, move_dis.y, move_dis.z)) * modelTrans;
}

float Mesh::speedreturn()
{
	return speed;
}

void Mesh::decide_world(glm::mat4 temp)
{
	rotate_world = temp;
}

void Mesh::change_solid(bool flag)
{
	solid = flag;
}