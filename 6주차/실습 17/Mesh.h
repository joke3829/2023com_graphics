#include "stdafx.h"

class Mesh {
private:
	unsigned int triangle_num;
	GLuint VAO, VBO[2], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> index;

	glm::mat4 FinalTransformMatrix;
	glm::mat4 transMatrix;
	glm::mat4 rotateMatrix;			//������
	glm::mat4 scaleMatrix;
	glm::mat4 rotate_world;			//������
	glm::mat4 finalrotate;			//�ڸ� ����
	glm::mat4 scale_world;
	bool ReadOBJ(std::string);		//OBJ�о����
	GLuint* shader;
public:
	float move_dis_x;
	float move_dis_y;
	float move_dis_z;
	float scale_size;
	float scale_world_size;
	float rotate_wolrd_rad;
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string);				// vao, vbo ���� ���� �� �ʱ�ȭ	�����ڿ� ������
	void Draw();			//�׸��� �Լ�
	void Rotate(float, float, float ,float);			// ȸ��
	void Scale(float);									// ����
	void Move(float, float, float);						// �̵�
	void Rotate_world(float, float, float, float);
	void Scale_world(float);
	void T_format();
	void M_format();
};