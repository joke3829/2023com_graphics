#include "stdafx.h"

class Mesh {
private:
	GLuint VAO, VBO[2], EBO;

	float coor[12]{};
	float color[12]{};
	unsigned int index[6]{};

	glm::mat4 FinalTransformMatrix;
	glm::mat4 transMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 firsttransMatrix;	//이동하고 회전해야 할때

	float scale_size;			// 스케일 사이즈
	glm::vec3 rotate_rad;		// 각 축에 따른 회전 각
	glm::vec3 trans_dis;		// 이동 거리
	GLuint* shader;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수
	void Update_rotate(float, float, float, float);
	void Update_trans(float, float, float);
	void Update_scale(float);
	void Update_first();
	void t_rotate();
	void f_rotate(bool);
	void s_move(bool);
	void b_scale(bool);
};