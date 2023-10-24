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

void Crane::x_Move(int way)
{
	switch (way) {
	case 4:
		cur_loc.x += 1;
		break;
	case 6:
		cur_loc.x -= 1;
	}
	body.Move(cur_loc);
	head.Move(cur_loc);
	for (int i = 0; i < 2; ++i) {
		front_arm[i].Move(cur_loc);
		raider[i].Move(cur_loc);
	}
}

glm::vec3 Crane::loc_return()
{
	return cur_loc;
}

glm::vec3 Crane::angle_return()
{
	return body_angle;
}

void Crane::rotate(int way)
{
	switch (way) {
	case 4:
		body_angle.x += 5;
		if (body_angle.x >= 360)
			body_angle.x = 0;
		break;
	case 6:
		body_angle.x -= 5;
		if (body_angle.x <= -360)
			body_angle.x = 0;
		break;
	}
	body.Rotate(body_angle);
	head.Rotate(body_angle + head_angle);
	for (int i = 0; i < 2; ++i) {
		front_arm[i].Rotate(body_angle);
		raider[i].Rotate(body_angle + head_angle);
	}
}

void Crane::Move(int way)
{
	glm::vec3 w_vector = glm::normalize(glm::vec3(glm::cos(glm::radians(90.0f - body_angle.x)), 0, glm::sin(glm::radians(90.0f - body_angle.x))));
	w_vector.x = w_vector.x * 0.5;
	w_vector.y = w_vector.y * 0.5;
	w_vector.z = w_vector.z * 0.5;
	switch (way) {
	case 8:
		cur_loc += w_vector;
		body.Move(cur_loc);
		head.Move(cur_loc);
		for (int i = 0; i < 2; ++i) {
			front_arm[i].Move(cur_loc);
			raider[i].Move(cur_loc);
		}	
		break;
	case 2:
		cur_loc -= w_vector;
		body.Move(cur_loc);
		head.Move(cur_loc);
		for (int i = 0; i < 2; ++i) {
			front_arm[i].Move(cur_loc);
			raider[i].Move(cur_loc);
		}
		break;
	}
}

void Crane::head_rotate(int way)
{
	switch (way) {
	case 4:
		head_angle.x += 5;
		break;
	case 6:
		head_angle.x -= 5;
		break;
	}
	body.Rotate(body_angle);
	head.Rotate(body_angle + head_angle);
	for (int i = 0; i < 2; ++i) {
		front_arm[i].Rotate(body_angle);
		raider[i].Rotate(body_angle + head_angle);
	}
}

void Crane::front_ani(int way)
{
	switch (way) {
	case 4:			// 벌어져라
		front_arm[0].front_rot(4);
		front_arm[1].front_rot(6);
		break;
	case 6:			// 펴져리
		break;
	}
}