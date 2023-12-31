
#include "Projection.h"

class Robot {
public:
	void Initialize(GLuint*);
	void Draw();
	void Move(int);
	void Rotate(int);
	void arm_legAni();
	void stand_ani();
	void speed_control(char);
	glm::vec3 return_loc();
	float return_rot();
	void angle_change(glm::vec3);
	void fallen(int way);
	bool check_crash(Mesh);
	bool check_crash(Robot);
	void Trans_init(glm::vec3);
	void death();
	bool state_check();
private:
	Mesh head;
	Mesh nose;
	Mesh body;
	Mesh arm[2]; // 0 ���� 1 ������
	Mesh leg[2];

	GLuint* shader;

	glm::vec3 cur_loc;
	float rotation_angle;
	float speed;
	float plus_angle;
	float max_angle;
	bool rArm_out;
	float Arm_angle;

	bool live;
};