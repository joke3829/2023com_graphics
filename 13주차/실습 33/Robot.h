
#include "Projection.h"

class Robot {
public:
	void Initialize(GLuint*, int);
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

	bool check_crash(Mesh, int);
	void Trans_init(glm::vec3);
	void death();
	bool state_check();

	void Move(glm::vec3);
	void Rotate(float);
private:
	Mesh head;
	Mesh nose;
	Mesh body;
	Mesh arm[2]; // 0 ¿ÞÂÊ 1 ¿À¸¥ÂÊ
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