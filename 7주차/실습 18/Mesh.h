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
	glm::mat4 firsttransMatrix;	//�̵��ϰ� ȸ���ؾ� �Ҷ�

	float scale_size;			// ������ ������
	glm::vec3 rotate_rad;		// �� �࿡ ���� ȸ�� ��
	glm::vec3 trans_dis;		// �̵� �Ÿ�
	GLuint* shader;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*);				// vao, vbo ���� ���� �� �ʱ�ȭ	�����ڿ� ������
	void Draw();			//�׸��� �Լ�
	void Update_rotate(float, float, float, float);
	void Update_trans(float, float, float);
	void Update_scale(float);
	void Update_first();
	void t_rotate();
	void f_rotate(bool);
	void s_move(bool);
	void b_scale(bool);
};