#define STB_IMAGE_IMPLEMENTATION
#include "Mesh.h"
#include "ShaderProgram.h"
#include "stb_image.h"

float Mesh::frame_late = 60.0f;

Mesh::Mesh() {};


Mesh::Mesh(std::string filename, std::string f_path, int w_size, int h_size) {
	Initialize(filename);
	Init_texture(f_path, w_size, h_size);
}

Mesh::~Mesh()
{
	// 사용했으면 반환해라
	glBindVertexArray(VAO);
	glDeleteBuffers(3, VBO);
	glDeleteVertexArrays(1, &VAO);

	std::cout << "Mesh 삭제" << '\n';
}

void Mesh::Initialize(std::string filename)
{
	if (not ReadOBJ(filename)) {
		std::cerr << "obj가 제대로 적용되지 않았습니다" << "\n";
		return;
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

	glBindVertexArray(VAO);

	int loc = glGetAttribLocation(shader->s_program, "vPos");
	// 좌표

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexs.size(), &vertexs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(shader->s_program, "vTexCoord");
	// 텍스처
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * texture_coor.size(), &texture_coor.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);

	loc = glGetAttribLocation(shader->s_program, "vNormal");
	// 정점 노말
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertex_normal.size(), &vertex_normal.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(loc);
	
 }

void Mesh::Init_texture(std::string filename, int w_size, int h_size)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int t_width = w_size;
	int t_height = h_size;
	int numberOfChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename.c_str(), &t_width, &t_height, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}

// 제대로 읽어 오면 true반환, 지금은 정점과 index만 저장, 추후 수정
bool Mesh::ReadOBJ(std::string filename)
{
	std::vector<glm::vec3> vertex_set;		// 정점 저장공간
	std::vector<glm::vec3> normal_set;		// 노말 저장공간
	std::vector<glm::vec3> uv_set;			// 텍스쳐 저장공간

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
				vertex_set.push_back(temp_vertex);
				stream.str("");
			}
			else if (str[0] == 'v' && str[1] == 'n') {
				stream.str(str);
				char novalue;
				glm::vec3 temp_vertex;
				stream >> novalue >> novalue >> temp_vertex.x >> temp_vertex.y >> temp_vertex.z;
				normal_set.push_back(temp_vertex);
				stream.str("");
			}
			else if (str[0] == 'v' && str[1] == 't') {
				stream.str(str);
				char novalue;
				glm::vec3 temp_vertex;
				stream >> novalue >> novalue >> temp_vertex.x >> temp_vertex.y >> temp_vertex.z;
				uv_set.push_back(temp_vertex);
				stream.str("");
			}
			else if (str[0] == 'f' && str[1] == ' ') {
				stream.str(str);
				int v_index[3]{};
				int n_index[3]{};
				int uv_index[3]{};
				char type;
				stream >> type >> v_index[0] >> type >> uv_index[0] >> type >> n_index[0]
					>> v_index[1] >> type >> uv_index[1] >> type >> n_index[1]
					>> v_index[2] >> type >> uv_index[2] >> type >> n_index[2];
				vertexs.push_back(vertex_set[v_index[0] - 1]);
				vertexs.push_back(vertex_set[v_index[1] - 1]);
				vertexs.push_back(vertex_set[v_index[2] - 1]);
				texture_coor.push_back(uv_set[uv_index[0] - 1]);
				texture_coor.push_back(uv_set[uv_index[1] - 1]);
				texture_coor.push_back(uv_set[uv_index[2] - 1]);
				vertex_normal.push_back(normal_set[n_index[0] - 1]);
				vertex_normal.push_back(normal_set[n_index[1] - 1]);
				vertex_normal.push_back(normal_set[n_index[2] - 1]);
				stream.str("");
			}
			str = "";
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
	loc = glGetUniformLocation(shader->s_program, "u_al");
	glUniform1fv(loc, 1, &u_al);
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, vertexs.size());
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

glm::vec2 Mesh::getRot() const
{
	return cur_rot;
}

void Mesh::set_ual(float n)
{
	u_al = n;
}

void Mesh::setSpd(float n)
{
	spd = n;
}

glm::vec3 Mesh::getLoc() const
{
	return cur_loc;
}

float Mesh::getSpd() const
{
	return spd;
}