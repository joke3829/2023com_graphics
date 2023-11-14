//===================================================================
// LightBox.h   ���� ���� ����(���� ������ �Ѵ�)
//===================================================================
#include "stdafx.h"

class LightBox {
public:
	LightBox();
	~LightBox();
	void Initialize(GLuint*, std::string);				// vao, vbo ���� ���� �� �ʱ�ȭ	�����ڿ� ������
	void Draw();			//�׸��� �Լ�

	void init_scale(float);
	void init_position(float, float, float);
	void init_rotate(float, float, float, float);

	void Move(int);					// �Ÿ� �ٲٱ� �Լ�
	void OutToVS();
	void Rotate(int);				// ���� �� �ٲٱ�
	void Lever();
protected:
private:
	unsigned int triangle_num;
	GLuint VAO, VBO[3], EBO;
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> vertex_normal;
	std::vector<unsigned int> index;

	glm::mat4 modelTrans;

	glm::mat4 scale;
	glm::mat4 trans;
	glm::mat4 rot;

	glm::vec3 init_pos;
	glm::vec3 cur_loc;
	glm::vec3 init_rot;
	glm::vec3 cur_rot;

	//������ ��
	glm::vec3 lightColor;
	glm::vec3 lightPos;

	bool ReadOBJ(std::string);		//OBJ�о����
	GLuint* shader;

	float dis;			// ������ �Ÿ�
};