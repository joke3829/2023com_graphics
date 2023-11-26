#include "stdafx.h"

class Mesh {
private:
	float spd;
	unsigned int triangle_num;
	GLuint VAO, VBO[3], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> vertex_normal;
	std::vector<unsigned int> index;

	glm::mat4 modelTrans;

	glm::vec3 init_pos;
	glm::vec3 cur_loc;
	glm::vec3 init_rot;
	glm::vec3 cur_rot;

	int p_cnt;
	bool select_ctor;

	bool ReadOBJ(std::string);		//OBJ�о����
	GLuint* shader;
public:
	Mesh();
	~Mesh();
	void Initialize(GLuint*, std::string, int);				// vao, vbo ���� ���� �� �ʱ�ȭ	�����ڿ� ������
	void Initialize(GLuint*, std::vector<glm::vec3>, int, float, float, float);
	void Draw();			//�׸��� �Լ�

	void init_scale(float);
	void init_position(float, float, float);
	void init_rotate(float, float, float, float);

	void Move(glm::vec3);
	void Rotate();

	void snowing(int);

	void x_rot();
	void y_rot();
	void z_rot();
};