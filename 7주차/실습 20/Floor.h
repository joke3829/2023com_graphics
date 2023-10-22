
#include "Line.h"

class Floor {
private:
	GLuint VAO, VBO[2];
	float coor[12];
	float color[12];
	glm::mat4 modelTrans;
	GLuint* shader;
public:
	void Initialize(GLuint*);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수
};