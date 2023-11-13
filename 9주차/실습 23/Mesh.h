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
	float b_radius;		// �ڽ� ������

	bool ReadOBJ(std::string);		//OBJ�о����
	GLuint* shader;

	bool right, up;

	
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string);				// vao, vbo ���� ���� �� �ʱ�ȭ	�����ڿ� ������
	void Draw();			//�׸��� �Լ�
	void setScale(float);
	void anime();
	void Move(glm::vec3);
	glm::vec3 getCenter();
	float getRadius(int);
	void setRight(bool);
	void setUp(bool);
	void setCur_loc();
	void setCur_loc(glm::vec3);
	void falling(int);
	void b_move(float);
};