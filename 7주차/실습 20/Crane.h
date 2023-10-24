#include "Projection.h"

class Crane {
	Mesh body;
	Mesh head;
	Mesh front_arm[2];
	Mesh raider[2];
	glm::vec3 cur_loc;			//���� ��ġ
	glm::vec3 body_angle;		// ���� ȸ�� ��
	glm::vec3 head_angle;		// �Ӹ� ȸ�� ��
	float f_angle;
	float f_merge;
	float t_angle;
	
public:
	Crane();
	~Crane();
	void Initialize(GLuint*);
	void Draw();
	void x_Move(int);
	void rotate(int);
	glm::vec3 loc_return();
	glm::vec3 angle_return();
	void Move(int);
	void head_rotate(int);
	void front_ani(int);
	void front_merge(int);
	void raider_rot(int);
};