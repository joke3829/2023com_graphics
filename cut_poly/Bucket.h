
#include "Cutter.h"

class Bucket {
public:
	void Initialize(GLuint*);
	void Move();
	void Draw();
	// 충돌 체크 함수 만들기
private:
	GLuint VAO, VBO[2];
	GLuint* shader;
	glm::mat4 modelTrans;

	float coor[12]{};
	float color[12]{};
	glm::vec2 left_b;		// 왼쪽 아래 좌표
	float width, height;	// 높이 폭

	bool move_left;
};