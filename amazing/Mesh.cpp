
#include "Mesh.h"
#include "ShaderProgram.h"

float Mesh::frame_late = 60.0f;

Mesh::Mesh() {};


Mesh::Mesh(std::string filename) {
	Initialize(filename);
}

Mesh::~Mesh()
{
	// 사용했으면 반환해라
	glBindVertexArray(VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(3, VBO);
	glDeleteVertexArrays(1, &VAO);

	std::cout << "Mesh 삭제" << '\n';
}

void Mesh::Initialize(std::string filename)
{
	upper = true;
	moving = true;

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> sspd(5.0, 8.0);

	scale_spd = sspd(dre);		// 랜덤으로 지정
	scale_value = 1.0;
	if (not ReadOBJ(filename)) {
		std::cerr << "obj가 제대로 적용되지 않았습니다" << "\n";
		return;
	}
	// 현재는 랜덤하게 컬러 지정

	std::uniform_real_distribution<float> urd_color(0.0, 1.0);

	float r; float g; float b;
	r = urd_color(dre);
	g = urd_color(dre);
	b = urd_color(dre);

	for (int i = 0; i < vertexs.size(); ++i) {
		glm::vec3 temp_color;
		temp_color.x = r;
		temp_color.y = g;
		temp_color.z = b;
		colors.push_back(temp_color);
	}

	modelTrans = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);

	cur_loc = glm::vec3(0.0);
	init_pos = glm::vec3(0.0);
	cur_rot = glm::vec3(0.0);
	init_rot = glm::vec3(0.0);

	shader = ShaderProgram::getShader();
	
	glUseProgram(shader->s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index.size(), &index.front(), GL_STATIC_DRAW);

	int loc = glGetAttribLocation(shader->s_program, "vPos");
	// 좌표

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexs.size(), &vertexs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(shader->s_program, "vColor");
	// 컬러
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(), &colors.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(shader->s_program, "vNormal");
	// 정점 노말
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertex_normal.size(), &vertex_normal.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);


 }


void Mesh::F_Initalize()
{
	vertexs.push_back(glm::vec3(-100, 0, -100));
	vertexs.push_back(glm::vec3(-100, 0, 100));
	vertexs.push_back(glm::vec3(100, 0, 100));
	vertexs.push_back(glm::vec3(100, 0, -100));

	colors.push_back(glm::vec3(0, 0, 1));
	colors.push_back(glm::vec3(0, 0, 1));
	colors.push_back(glm::vec3(0, 0, 1));
	colors.push_back(glm::vec3(0, 0, 1));

	vertex_normal.push_back(glm::vec3(0, 1, 0));
	vertex_normal.push_back(glm::vec3(0, 1, 0));
	vertex_normal.push_back(glm::vec3(0, 1, 0));
	vertex_normal.push_back(glm::vec3(0, 1, 0));

	modelTrans = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);

	cur_loc = glm::vec3(0.0);
	init_pos = glm::vec3(0.0);
	cur_rot = glm::vec3(0.0);
	init_rot = glm::vec3(0.0);

	shader = ShaderProgram::getShader();

	glUseProgram(shader->s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);

	glBindVertexArray(VAO);

	int loc = glGetAttribLocation(shader->s_program, "vPos");
	// 좌표

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexs.size(), &vertexs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(shader->s_program, "vColor");
	// 컬러
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(), &colors.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(shader->s_program, "vNormal");
	// 정점 노말
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertex_normal.size(), &vertex_normal.front(), GL_STATIC_DRAW);
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

void Mesh::Render() const
{
	int loc = glGetUniformLocation(shader->s_program, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelTrans));
	loc = glGetUniformLocation(shader->s_program, "rotateMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(rotateMatrix));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3 * triangle_num, GL_UNSIGNED_INT, 0);
}

void Mesh::F_Render() const
{
	int loc = glGetUniformLocation(shader->s_program, "transform");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelTrans));
	loc = glGetUniformLocation(shader->s_program, "rotateMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(rotateMatrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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
	temp = glm::mat4(1.0f);
	rotateMatrix = glm::rotate(temp, glm::radians(rad), glm::vec3(x, y, z)) * rotateMatrix;
}

void Mesh::setLoc(glm::vec3 new_loc)
{
	glm::mat4 temp(1.0f);
	modelTrans = glm::translate(temp, -cur_loc) * modelTrans; temp = glm::mat4(1.0f);
	cur_loc = new_loc;
	modelTrans = glm::translate(temp, cur_loc) * modelTrans;
}

void Mesh::setRot(glm::vec2 new_rot)
{
	glm::mat4 temp(1.0f);

	modelTrans = glm::translate(temp, -cur_loc) * modelTrans; temp = glm::mat4(1.0f);

	modelTrans = glm::rotate(temp, glm::radians(-(360 - cur_rot.x)), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);

	rotateMatrix = glm::rotate(temp, glm::radians(-(360 - cur_rot.x)), glm::vec3(0, 1, 0)) * rotateMatrix; temp = glm::mat4(1.0f);

	modelTrans = glm::rotate(temp, glm::radians(-cur_rot.y), glm::vec3(0, 0, 1)) * modelTrans; temp = glm::mat4(1.0f);

	rotateMatrix = glm::rotate(temp, glm::radians(-cur_rot.y), glm::vec3(0, 0, 1)) * rotateMatrix; temp = glm::mat4(1.0f);

	cur_rot = new_rot;

	modelTrans = glm::rotate(temp, glm::radians(cur_rot.y), glm::vec3(0, 0, 1)) * modelTrans; temp = glm::mat4(1.0f);

	rotateMatrix = glm::rotate(temp, glm::radians(cur_rot.y), glm::vec3(0, 0, 1)) * rotateMatrix; temp = glm::mat4(1.0f);

	modelTrans = glm::rotate(temp, glm::radians((360 - cur_rot.x)), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);

	rotateMatrix = glm::rotate(temp, glm::radians((360 - cur_rot.x)), glm::vec3(0, 1, 0)) * rotateMatrix; temp = glm::mat4(1.0f);

	modelTrans = glm::translate(temp, cur_loc) * modelTrans; temp = glm::mat4(1.0f);
}

void Mesh::anime_1()
{
	glm::mat4 temp(1.0f);
	if (0 != scale_value)
		modelTrans = glm::scale(temp, glm::vec3(1, 1.0f / scale_value, 1)) * modelTrans;
	temp = glm::mat4(1.0f);

	if (upper) {
		scale_value = scale_value + (scale_spd / frame_late);
		if (scale_value >= 20) {
			upper = false;
			scale_value = 20;
		}
		modelTrans = glm::scale(temp, glm::vec3(1, scale_value, 1)) * modelTrans;
	}
	else {
		scale_value = scale_value - (scale_spd / frame_late);
		if (scale_value <= 1) {
			scale_value = 1;
			upper = true;
		}
		modelTrans = glm::scale(temp, glm::vec3(1, scale_value, 1)) * modelTrans;
	}
}

void Mesh::anime_2()
{
	end = clock();
	double time = double(end - start) / CLOCKS_PER_SEC;
	if (delay_time < time)
		moving = true;

	glm::mat4 temp(1.0f);

	if (0 != scale_value)
		modelTrans = glm::scale(temp, glm::vec3(1, 1.0f / scale_value, 1)) * modelTrans;
	temp = glm::mat4(1.0f);


	if (moving) {
		if (upper) {
			scale_value = scale_value + (scale_spd / frame_late);
			if (scale_value >= 20) {
				upper = false;
				scale_value = 20;
			}
			modelTrans = glm::scale(temp, glm::vec3(1, scale_value, 1)) * modelTrans;
		}
		else {
			scale_value = scale_value - (scale_spd / frame_late);
			if (scale_value <= 1) {
				scale_value = 1;
				upper = true;
			}
			modelTrans = glm::scale(temp, glm::vec3(1, scale_value, 1)) * modelTrans;
		}
	}
}

void Mesh::anime_3()
{

}

void Mesh::back_scale()
{
	glm::mat4 temp(1.0f);
	if(scale_value > 1)
		modelTrans = glm::scale(temp, glm::vec3(1, 1.0f / scale_value, 1)) * modelTrans;
	scale_value = 1;
}

void Mesh::setSpd(float ss)
{
	scale_spd = ss;
}

void Mesh::ready_ani_1()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> sspd(5.0, 8.0);

	back_scale();
	setSpd(sspd(dre));

	moving = true;
	upper = true;
}

void Mesh::ready_ani_2(int n)
{
	back_scale();
	setSpd(5);


	delay_time = n * 0.2;
	start = clock();

	moving = false;
	upper = true;
}

void Mesh::ready_ani_3(int n)
{
	back_scale();
	setSpd(5);


	delay_time = n * 0.2;
	start = clock();

	moving = false;
	upper = true;
}