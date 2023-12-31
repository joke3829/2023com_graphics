#include "stdafx.h"

class Mesh {
private:
	unsigned int triangle_num;
	GLuint VAO, VBO[2], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> index;

	glm::mat4 modelTrans;

	glm::vec3 cur_loc;
	float radius;
	float b_radius;		// 박스 반지름

	bool ReadOBJ(std::string);		//OBJ읽어오기
	GLuint* shader;

	bool right, up;

	
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수
	void setScale(float);
	void anime();
	void Move(glm::vec3);
	glm::vec3 getCenter();
	float getRadius(int);
	void setRight(bool);
	void setUp(bool);
	void setCur_loc();
	void setCur_loc(glm::vec3);
	void falling(int);
	void b_move(float);
};