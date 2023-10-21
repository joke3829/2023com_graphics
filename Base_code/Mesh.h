#include "stdafx.h"

class Mesh {
private:
	unsigned int triangle_num;
	GLuint VAO, VBO[2], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> index;

	glm::mat4 FinalTransformMatrix;
	glm::mat4 transMatrix;
	glm::mat4 rotateMatrix;			//자전용
	glm::mat4 scaleMatrix;
	glm::mat4 rotate_world;			//공전용
	glm::mat4 finalrotate;			//자리 잡기용
	glm::mat4 scale_world;
	bool ReadOBJ(std::string);		//OBJ읽어오기
	GLuint* shader;
public:
	float move_dis_x;
	float move_dis_y;
	float move_dis_z;
	float scale_size;
	float scale_world_size;
	float rotate_wolrd_rad;
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수
	void Rotate(float, float, float ,float);			// 회전
	void Scale(float);									// 신축
	void Move(float, float, float);						// 이동
	void Rotate_world(float, float, float, float);
	void Scale_world(float);
	void T_format();
	void M_format();
};