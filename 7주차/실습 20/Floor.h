
#include "Line.h"

class Floor {
private:
	GLuint VAO, VBO[2];
	float coor[12];
	float color[12];
	glm::mat4 modelTrans;
	GLuint* shader;
public:
	void Initialize(GLuint*);				// vao, vbo ���� ���� �� �ʱ�ȭ	�����ڿ� ������
	void Draw();			//�׸��� �Լ�
};