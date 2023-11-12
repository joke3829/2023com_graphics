#include "stdafx.h"

class Mesh {
private:
	unsigned int triangle_num;
	GLuint VAO, VBO[2], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> index;

	glm::mat4 modelTrans;

	glm::vec3 init_pos;
	glm::vec3 cur_loc;
	glm::vec3 init_rot;
	glm::vec3 cur_rot;

	bool ReadOBJ(std::string);		//OBJ읽어오기
	bool dropcube;					// 끝까지 떨어지자
	bool moving_cube;				// 바닥에 붙자
	bool lever;
	GLuint* shader;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Initialize(GLuint*, std::string, int color_type);
	void Draw();			//그리기 함수

	void init_scale(float);
	void init_position(float, float, float);
	void init_rotate(float, float, float, float);

	void Move(glm::vec3);
	void Rotate(glm::vec3);
	void swing(int, float);

	void death(int);
	
	void change_drop(int);
	void change_lever();

	bool getMoving();
	bool getDropcube();
	bool getLever();

	glm::vec3 return_loc();
	std::vector<glm::vec3> return_vertex();
};