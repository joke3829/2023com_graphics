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
	f_angle = 0;
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
	f_merge = t_angle = 0;
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
	case 4:			// 펴져라
		if (f_angle < 90) {
			front_arm[0].front_rot(4);
			front_arm[1].front_rot(6);
			f_angle += 5;
		}
		break;
	case 6:			// 모여라
		if (f_angle > 0) {
			front_arm[0].front_rot(6);
			front_arm[1].front_rot(4);
			f_angle -= 5;
		}
		break;
	}
}

void Crane::front_merge(int way)
{
	switch (way) {
	case 4:
		if (f_merge > 0) {
			f_merge -= 0.1;
			front_arm[0].front_merge(4);
			front_arm[1].front_merge(6);
		}
		break;
	case 6:			// 모여라
		if (f_angle > 0) {
			front_arm[0].front_rot(6);
			front_arm[1].front_rot(4);
			f_angle -= 5;
		}
		else {
			if (f_merge < 0.6) {
				f_merge += 0.1;
				front_arm[0].front_merge(6);
				front_arm[1].front_merge(4);
			}
		}
		break;
	}
}

void Crane::raider_rot(int way)
{
	switch (way) {
	case 4:
		if (t_angle > -90) {
			t_angle -= 5;
			raider[0].raider_rot(4);
			raider[1].raider_rot(6);
		}
		break;
	case 6:
		if (t_angle < 90) {
			t_angle += 5;
			raider[0].raider_rot(6);
			raider[1].raider_rot(4);
		}
		break;
	}
}

void Crane::init_state()
{
	cur_loc = body_angle = head_angle = glm::vec3(0, 0, 0);
	body.Move(cur_loc);
	body.Rotate(body_angle);
	head.Move(cur_loc);
	head.Rotate(body_angle + head_angle);
	for (int i = 0; i < 2; ++i) {
		front_arm[i].Move(cur_loc);
		front_arm[i].Rotate(body_angle + head_angle);
		raider[i].Move(cur_loc);
		raider[i].Rotate(body_angle + head_angle);
	}
	for (; f_angle != 0;) {
		front_arm[0].front_rot(6);
		front_arm[1].front_rot(4);
		f_angle -= 5;
	}
	for (; f_merge > 0; ) {
		f_merge -= 0.1;
		front_arm[0].front_merge(4);
		front_arm[1].front_merge(6);
	}
	for (; t_angle != 0;) {
		if (t_angle > 0) {
			t_angle -= 5;
			raider[0].raider_rot(4);
			raider[1].raider_rot(6);
		}
		else {
			t_angle += 5;
			raider[0].raider_rot(6);
			raider[1].raider_rot(4);
		}
	}
}