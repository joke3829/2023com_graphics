#include "LightBox.h"

LightBox::LightBox() {
}

LightBox::~LightBox()
{
}

void LightBox::Initialize(GLuint* shaderprogram, std::string filename)
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
		temp_color.x = 1;
		temp_color.y = 1;
		temp_color.z = 1;
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
	glGenBuffers(3, VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index.size(), &index.front(), GL_STATIC_DRAW);

	GLuint loc = glGetAttribLocation(*shader, "vPos");
	std::cout << loc << std::endl;
	// 좌표
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexs.size(), &vertexs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(*shader, "vColor");
	// 컬러
	std::cout << loc << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(), &colors.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);
	std::cout << "test1" << std::endl;

	loc = glGetAttribLocation(*shader, "vNormal");
	// 정점 노말
	std::cout << loc << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertex_normal.size(), &vertex_normal.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);
	std::cout << "test2 " << std::endl;

	lightColor = glm::vec3(1.0);
	trans = glm::mat4(1.0f);
	rot = glm::mat4(1.0f);
	scale = glm::mat4(1.0f);
	init_scale(0.2);
	dis = 10;
	trans = glm::translate(trans, glm::vec3(dis, 0, 0));
}

// 제대로 읽어 오면 true반환, 지금은 정점과 index만 저장, 추후 수정
bool LightBox::ReadOBJ(std::string filename)
{
	triangle_num = 0;
	char c;
	std::string str;
	std::ifstream fin(filename);
	if (not fin) {
		std::cerr << "obj파일을 찾지 못했습니다. " << "\n";
		return false;
	}
	std::vector<glm::vec3> subVn;		// 정점수와 노말수가 안맞을 때 사용할 변수
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
			else if (str[0] == 'v' && str[1] == 'n') {
				stream.str(str);
				char novalue;
				glm::vec3 temp_vertex;
				stream >> novalue >> novalue >> temp_vertex.x >> temp_vertex.y >> temp_vertex.z;
				vertex_normal.push_back(temp_vertex);
				subVn.push_back(temp_vertex);
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

	if (vertexs.size() != vertex_normal.size()) {

		struct Group {
			std::vector<unsigned int> factor;
			unsigned int normal;
		};
		str = "";

		std::vector<Group> group_set;
		fin.close();
		fin.open(filename);

		while (not fin.eof()) {
			fin >> c;
			str += c;
			if (c == '\n') {
				if (str[0] == 's') {
					Group g_temp;
					group_set.push_back(g_temp);
				}
				else if (str[0] == 'f' && str[1] == ' ') {
					stream.str(str);
					char type;
					int t_normal;
					int novalue;
					int temp_index[3];
					int real_index[3];
					stream >> type >> temp_index[0] >> type >> novalue >> type >> t_normal
						>> temp_index[1] >> type >> novalue >> type >> t_normal
						>> temp_index[2] >> type >> novalue >> type >> t_normal;
					for (int i = 0; i < 3; ++i) {
						real_index[i] = temp_index[i] - 1;
						group_set[group_set.size() - 1].factor.push_back(real_index[i]);
					}
					--t_normal;
					group_set[group_set.size() - 1].normal = t_normal;


					stream.str("");
				}
				str = "";
			}
		}

		vertex_normal.clear();
		for (int i = 0; i < vertexs.size(); ++i) {
			int num_near = 0;		// 근접한 그룹 수
			glm::vec3 f_normal(0, 0, 0);		// 평균낸 정점 노말
			for (int j = 0; j < group_set.size(); ++j) {
				for (int k = 0; k < group_set[j].factor.size(); ++k) {
					if (group_set[j].factor[k] == i) {
						num_near++;
						f_normal += subVn[group_set[j].normal];
						break;
					}
				}
			}
			f_normal.x = f_normal.x / num_near;
			f_normal.y = f_normal.y / num_near;
			f_normal.z = f_normal.z / num_near;
			vertex_normal.push_back(glm::normalize(f_normal));
		}
	}
	return true;
}

void LightBox::Draw()
{
	glm::mat4 temp(1.0f);
	modelTrans = rot * trans * scale;
	lightPos = glm::vec3(0, 0, 0);
	lightPos = glm::vec3(modelTrans * glm::vec4(lightPos, 1.0f));
	/*modelTrans = glm::rotate(temp, glm::radians(-cur_rot.y), glm::vec3(0, 1, 0)) * modelTrans;
	temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(2, 0, 0)) * modelTrans;
	temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(cur_rot.y), glm::vec3(0, 1, 0)) * modelTrans;*/
	unsigned int loc = glGetUniformLocation(*shader, "lightPos");
	glUniform3f(loc, lightPos.x, lightPos.y, lightPos.z);
	loc = glGetUniformLocation(*shader, "lightColor");
	glUniform3f(loc, lightColor.x, lightColor.y, lightColor.z);
	loc = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelTrans));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3 * triangle_num, GL_UNSIGNED_INT, 0);
}

void LightBox::init_scale(float size)
{
	scale = glm::scale(scale, glm::vec3(size, size, size));
}

void LightBox::init_position(float x, float y, float z)
{
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, glm::vec3(x, y, z)) * modelTrans;
	init_pos = glm::vec3(x, y, z);
}

void LightBox::init_rotate(float rad, float x, float y, float z)
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

void LightBox::Move(int way)
{
	switch (way) {
	case 4:
		dis += 1;
		break;
	case 6:
		dis -= 1;
		break;
	}
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(dis, 0, 0));
}

void LightBox::Rotate(int way)
{
	switch (way) {
	case 4:
		cur_rot.y += 5;
		break;
	case 6:
		cur_rot.y -= 5;
		break;
	}
	rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, glm::radians(cur_rot.y), glm::vec3(0, 1, 0));
}

void LightBox::Lever()
{
	if (lightColor == glm::vec3(0, 0, 0))
		lightColor = glm::vec3(1, 1, 1);
	else
		lightColor = glm::vec3(0, 0, 0);
}