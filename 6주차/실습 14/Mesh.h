#include "stdafx.h"

class Mesh {
private:
	int vari;
	unsigned int triangle_num;
	GLuint VAO, VBO[2];
	float coor[72]{};
	float color[72]{};

	glm::mat4 FinalTransformMatrix;
	glm::mat4 transMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;
	bool ReadOBJ(std::string);		//OBJ읽어오기
	GLuint* shader;
	bool* visible;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string, int);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수
	void Rotate(float, float, float ,float);			// 회전
	void Scale(float);									// 신축
	void Move(float, float, float);						// 이동
	void change_visible(int);
	void change_visible(bool);
};