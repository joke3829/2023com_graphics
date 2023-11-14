#include "stdafx.h"

class Mesh {
private:
	unsigned int triangle_num;
	GLuint VAO, VBO[3], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> vertex_normal;
	std::vector<unsigned int> index;

	glm::mat4 modelTrans;

	glm::vec3 init_pos;
	glm::vec3 cur_loc;
	glm::vec3 init_rot;
	glm::vec3 cur_rot;

	bool ReadOBJ(std::string);		//OBJ읽어오기
	GLuint* shader;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수

	void init_scale(float);
	void init_position(float, float, float);
	void init_rotate(float, float, float, float);

	void Move(glm::vec3);
	void Rotate(glm::vec3);
};