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
	bool ReadOBJ(std::string);		//OBJ�о����
	GLuint* shader;
	bool* visible;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string, int);				// vao, vbo ���� ���� �� �ʱ�ȭ	�����ڿ� ������
	void Draw();			//�׸��� �Լ�
	void Rotate(float, float, float ,float);			// ȸ��
	void Scale(float);									// ����
	void Move(float, float, float);						// �̵�
	void change_visible(int);
	void change_visible(bool);
};