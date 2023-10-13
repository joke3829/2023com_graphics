#include "stdafx.h"

class Mesh {
	unsigned int triangle_num;
	GLuint VAO, VBO[2], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> index;

	glm::mat4 FinalTransformMatrix;
	glm::mat4 transMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;
	bool ReadOBJ(std::string);		//OBJ읽어오기
	GLuint* shader;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*);				//vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수
};