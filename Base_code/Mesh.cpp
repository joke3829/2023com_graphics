
#include "Line.h"

Mesh::Mesh() {
}

Mesh::~Mesh()
{
}

void Mesh::Initialize(GLuint* shaderprogram, std::string filename, int v)
{
	vari = v;
	if (not ReadOBJ(filename)) {
		std::cerr << "obj�� ����� ������� �ʾҽ��ϴ�" << "\n";
		return;
	}
	// ����� �����ϰ� �÷� ����

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

	FinalTransformMatrix = glm::mat4(1.0f);
	transMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);

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

	visible = new bool[triangle_num];
	for (int i = 0; i < triangle_num; ++i) {
		visible[i] = true;
	}
}
// ����� �о� ���� true��ȯ, ������ ������ index�� ����, ���� ����
bool Mesh::ReadOBJ(std::string filename)
{
	triangle_num = 0;
	char c;
	std::string str;
	std::ifstream fin(filename);
	if (not fin) {
		std::cerr << "obj������ ã�� ���߽��ϴ�. " << "\n";
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
	FinalTransformMatrix = transMatrix * rotateMatrix * scaleMatrix;
	unsigned int loc = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(FinalTransformMatrix));
	glBindVertexArray(VAO);
	if (visible[0]) {
		switch (vari) {
		case 0:
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			break;
		case 1:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		}
	}
	if (visible[1]) {
		switch (vari) {
		case 0:
			//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			break;
		case 1:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		}
	}
	if (visible[2]) {
		switch (vari) {
		case 0:
			//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			break;
		case 1:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		}
	}
	if (visible[3]) {
		switch (vari) {
		case 0:
			//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			break;
		case 1:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
		}
	}
	//glDrawElements(GL_TRIANGLES, 3 * triangle_num, GL_UNSIGNED_INT, 0);
}

void Mesh::Scale(float size)
{
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(size, size, size));
}

void Mesh::Rotate(float rad, float x, float y, float z)
{
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rad), glm::vec3(x, y, z));
}

void Mesh::Move(float x, float y, float z)
{
	transMatrix = glm::translate(transMatrix, glm::vec3(x, y, z));
}