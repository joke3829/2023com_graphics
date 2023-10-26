
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
private:
	Mesh head;
	Mesh nose;
	Mesh body;
	Mesh arm[2]; // 0 왼쪽 1 오른쪽
	Mesh leg[2];

	GLuint* shader;

	glm::vec3 cur_loc;
	float rotation_angle;
	float speed;
	float plus_angle;
	float max_angle;
	bool rArm_out;
	float Arm_angle;
};