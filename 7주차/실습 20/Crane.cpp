#include "Crane.h"

Crane::Crane()
{

}

Crane::~Crane()
{

}

void Crane::Initialize(GLuint* shaderProgram)
{
	cur_loc = head_angle = body_angle = glm::vec3(0, 0, 0);
	body.Initialize(shaderProgram, "crane\\crane_body.obj");
	head.Initialize(shaderProgram, "crane\\crane_head.obj");
	for (int i = 0; i < 2; ++i) {
		front_arm[i].Initialize(shaderProgram, "crane\\crane_arm.obj");
		raider[i].Initialize(shaderProgram, "crane\\crane_arm.obj");
	}
	body.init_scale(0.2);
	head.init_scale(0.2);
	front_arm[0].init_scale(0.2); front_arm[1].init_scale(0.2);
	raider[0].init_scale(0.2); raider[1].init_scale(0.2);
	head.init_position(0, 5 * 0.2, 0);
	raider[0].init_position(1.5 * 0.2, 8 * 0.2, 0);
	raider[1].init_position(-1.5 * 0.2, 8 * 0.2, 0);
	front_arm[0].init_rotate(90, 1, 0, 0); front_arm[0].init_position(3 * 0.2, 2.5 * 0.2, 5 * 0.2);
	front_arm[1].init_rotate(90, 1, 0, 0); front_arm[1].init_position(-3 * 0.2, 2.5 * 0.2, 5 * 0.2);
}

void Crane::Draw()
{
	body.Draw();
	head.Draw();
	for (int i = 0; i < 2; ++i) {
		front_arm[i].Draw();
		raider[i].Draw();
	}
}