
#include "Line.h"

Mesh::Mesh() {
}

Mesh::~Mesh()
{
}

void Mesh::Initialize(GLuint* shaderprogram, std::string filename, int v)
{
	vari = v;
	switch (vari) {
	case 0://사면체
		// 0번 면
		coor[0] = 0.0000; coor[1] = 2.5000; coor[2] = 0.0333;			// 0번 점
		coor[3] = -0.0125; coor[4] = -2.5000; coor[5] = 3.1261;			// 1번 점
		coor[6] = 2.6622; coor[7] = -2.5000; coor[8] = -1.7989;			// 2번 점
		// 1
		coor[9] = 0.0000; coor[10] = 2.5000; coor[11] = 0.0333;			// 0번 점
		coor[12] = 2.6622; coor[13] = -2.5000; coor[14] = -1.7989;			// 2번 점
		coor[15] = -2.6622; coor[16] = -2.5000; coor[17] = -1.7989;			// 3번 점
		// 2
		coor[18] = 0.0000; coor[19] = 2.5000; coor[20] = 0.0333;			// 0번 점
		coor[21] = -2.6622; coor[22] = -2.5000; coor[23] = -1.7989;			// 3번 점
		coor[24] = -0.0125; coor[25] = -2.5000; coor[26] = 3.1261;			// 1번 점
		// 3
		coor[27] = -0.0125; coor[28] = -2.5000; coor[29] = 3.1261;			// 1번 점
		coor[30] = -2.6622; coor[31] = -2.5000; coor[32] = -1.7989;			// 3번 점
		coor[33] = 2.6622; coor[34] = -2.5000; coor[35] = -1.7989;			// 2번 점
		triangle_num = 4;
		break;
	case 1://육면체
		coor[0] = -5; coor[1] = -5; coor[2] = 5;			// 0번 점
		coor[3] = -5; coor[4] = -5; coor[5] = -5;			// 1번 점
		coor[6] = 5; coor[7] = -5; coor[8] = -5;			// 2번 점
		coor[9] = 5; coor[10] = -5; coor[11] = 5;			// 3번 점
		//1면
		coor[12] = -5; coor[13] = -5; coor[14] = 5;			// 0번 점
		coor[15] = 5; coor[16] = -5; coor[17] = 5;			// 3번 점
		coor[18] = 5; coor[19] = 5; coor[20] = 5;			// 5번 점
		coor[21] = -5; coor[22] = 5; coor[23] = 5;			// 4번 점
		// 2면
		coor[24] = 5; coor[25] = 5; coor[26] = 5;			// 5번 점
		coor[27] = 5; coor[28] = -5; coor[29] = 5;			// 3번 점
		coor[30] = 5; coor[31] = -5; coor[32] = -5;			// 2번 점
		coor[33] = 5; coor[34] = 5; coor[35] = -5;			// 6번 점
		//3 면
		coor[36] = 5; coor[37] = -5; coor[38] = -5;			// 2번 점
		coor[39] = -5; coor[40] = -5; coor[41] = -5;		// 1번 점
		coor[42] = -5; coor[43] = 5; coor[44] = -5;			// 7번 점
		coor[45] = 5; coor[46] = 5; coor[47] = -5;			// 6번 점
		// 4면
		coor[48] = -5; coor[49] = -5; coor[50] = 5;			// 0번 점
		coor[51] = -5; coor[52] = -5; coor[53] = -5;		// 1번 점
		coor[54] = -5; coor[55] = 5; coor[56] = -5;			// 7번 점
		coor[57] = -5; coor[58] = 5; coor[59] = 5;			// 4번 점
		// 뚜껑
		coor[60] = 5; coor[61] = 5; coor[62] = -5;			// 6번 점
		coor[63] = -5; coor[64] = 5; coor[65] = -5;			// 7번 점
		coor[66] = -5; coor[67] = 5; coor[68] = 5;			// 4번 점
		coor[69] = 5; coor[70] = 5; coor[71] = 5;			// 5번 점
		triangle_num = 6;
		break;
	}
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd_color(0.0, 1.0);

	for (int i = 0; i < 72; i += 3) {
		color[i] = urd_color(dre);
		color[i + 1] = urd_color(dre);
		color[i + 2] = urd_color(dre);
	}

	FinalTransformMatrix = glm::mat4(1.0f);
	transMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);

	shader = shaderprogram;
	glUseProgram(*shader);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO);

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

	visible = new bool[triangle_num];
	for (int i = 0; i < triangle_num; ++i) {
		visible[i] = true;
	}
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
	/*while (not fin.eof()) {
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
	}*/
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
			glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		case 1:
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			break;
		}
	}
	if (visible[1]) {
		switch (vari) {
		case 0:
			glDrawArrays(GL_TRIANGLES, 3, 3);
			break;
		case 1:
			glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
			break;
		}
	}
	if (visible[2]) {
		switch (vari) {
		case 0:
			glDrawArrays(GL_TRIANGLES, 6, 3);
			break;
		case 1:
			glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
			break;
		}
	}
	if (visible[3]) {
		switch (vari) {
		case 0:
			glDrawArrays(GL_TRIANGLES, 9, 3);
			break;
		case 1:
			glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
			break;
		}
	}
	if (triangle_num == 6) {
		if (visible[4]) {
			glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
		}
		if (visible[5]) {
			glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
		}
	}
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

void Mesh::change_visible(int num)
{
	if (visible[num]) {
		visible[num] = false;
	}
	else
		visible[num] = true;
}

void Mesh::change_visible(bool flag)
{
	for (int i = 0; i < triangle_num; ++i) {
		visible[i] = flag;
	}
}