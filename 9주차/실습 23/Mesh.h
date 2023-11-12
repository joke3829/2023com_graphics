#include "stdafx.h"

class Mesh {
private:
	unsigned int triangle_num;
	GLuint VAO, VBO[2], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> index;

	glm::mat4 modelTrans;

	glm::vec3 cur_loc;
	float radius;


	bool ReadOBJ(std::string);		//OBJ�о����
	GLuint* shader;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string);				// vao, vbo ���� ���� �� �ʱ�ȭ	�����ڿ� ������
	void Draw();			//�׸��� �Լ�
	void setScale(float);
};