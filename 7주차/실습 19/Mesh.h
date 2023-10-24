#include "stdafx.h"

class Mesh {
private:
	unsigned int triangle_num;
	GLuint VAO, VBO[2], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> index;
	bool solid;

	glm::vec3 move_dis;
	float rotate_rad;
	float speed;
	glm::mat4 finalMatrix;
	glm::mat4 modelTrans;
	glm::mat4 rotate_world;
	glm::mat4 calculate_mat;
	bool ReadOBJ(std::string);		//OBJ읽어오기
	GLuint* shader;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string, float, float);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수
	void Rotate(float, float, float ,float);			// 회전
	void Scale(float);									// 신축
	void Move(float, float, float);						// 이동
	void Rotate_world();
	float speedreturn();
	void decide_world(float, float, float, float);
	void change_solid(bool);
};