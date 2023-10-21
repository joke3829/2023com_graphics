#include "Circle.h"

class Planet {
	Mesh planet;		// 행성
	Mesh satellite;		// 위성
	Move_Circle orbit;

	glm::vec3 move_dis;
	float rad, speed;
	GLuint* shader;
public:
	void Initialize(GLuint*, float);
	void anime();
	void Draw();
	void Move();
	void decide_world(float, float, float, float);
	void change_solid(bool);
};