
#include "Cutter.h"

class Bucket {
public:
	void Initialize(GLuint*);
	void Move();
	void Draw();
	// �浹 üũ �Լ� �����
private:
	GLuint VAO, VBO[2];
	GLuint* shader;
	glm::mat4 modelTrans;

	float coor[12]{};
	float color[12]{};
	glm::vec2 left_b;		// ���� �Ʒ� ��ǥ
	float width, height;	// ���� ��

	bool move_left;
};