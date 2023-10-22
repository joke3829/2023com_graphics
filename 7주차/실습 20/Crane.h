#include "Projection.h"

class Crane {
	Mesh body;
	Mesh head;
	Mesh front_arm[2];
	Mesh raider[2];
	glm::vec3 cur_loc;			//현재 위치
	glm::vec3 body_angle;		// 몸통 회전 각
	glm::vec3 head_angle;		// 머리 회전 각
	
public:
	Crane();
	~Crane();
	void Initialize(GLuint*);
	void Draw();
};