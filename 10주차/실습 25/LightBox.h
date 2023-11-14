//===================================================================
// LightBox.h   빛을 내는 상자(조명 역할을 한다)
//===================================================================
#include "stdafx.h"

class LightBox {
public:
	LightBox();
	~LightBox();
	void Initialize(GLuint*, std::string);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수

	void init_scale(float);
	void init_position(float, float, float);
	void init_rotate(float, float, float, float);

	void Move(int);					// 거리 바꾸기 함수
	void OutToVS();
	void Rotate(int);				// 공전 각 바꾸기
	void Lever();
protected:
private:
	unsigned int triangle_num;
	GLuint VAO, VBO[3], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> vertex_normal;
	std::vector<unsigned int> index;

	glm::mat4 modelTrans;

	glm::mat4 scale;
	glm::mat4 trans;
	glm::mat4 rot;

	glm::vec3 init_pos;
	glm::vec3 cur_loc;
	glm::vec3 init_rot;
	glm::vec3 cur_rot;

	//조명의 색
	glm::vec3 lightColor;
	glm::vec3 lightPos;

	bool ReadOBJ(std::string);		//OBJ읽어오기
	GLuint* shader;

	float dis;			// 원점과 거리
};