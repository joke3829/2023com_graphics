
#include "Cube.h"

class Triangle {
	GLuint VAO, VBO[2];

	float coor[9]{};
	float color[9]{};

	bool fold;
	bool state_r;

	glm::mat4 FinalTransformMatrix;
	glm::mat4 transMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 first_rotate;

	float fold_size;
	float scale_size;			// ������ ������
	glm::vec3 rotate_rad;		// �� �࿡ ���� ȸ�� ��
	glm::vec3 trans_dis;		// �̵� �Ÿ�
	GLuint* shader;
public:
	Triangle();
	~Triangle();
	void Initialize(GLuint*);				// vao, vbo ���� ���� �� �ʱ�ȭ	�����ڿ� ������
	void Draw();			//�׸��� �Լ�
	void Update_rotate(float, float, float, float);
	void Update_trans(float, float, float);
	void Update_scale(float);
	void change_bfold(bool);
	void change_state(bool);
	void fold_poly();
};