#include "Robot.h"

void Robot::Initialize(GLuint* shaderProgram)
{
	speed = 0.1;
	shader = shaderProgram;
	head.Initialize(shader, "robot\\head.obj");
	nose.Initialize(shader, "robot\\nose.obj");
	body.Initialize(shader, "robot\\body.obj");
	for (int i = 0; i < 2; ++i) {	//哭率 坷弗率
		arm[i].Initialize(shader, "robot\\arm_leg.obj");
		leg[i].Initialize(shader, "robot\\arm_leg.obj");
	}
	head.init_position(0, 24, 0);
	body.init_position(0, 12, 0);
	arm[0].init_position(-6, 12, 0); arm[1].init_position(6, 12, 0);
	leg[0].init_position(-2, 0, 0); leg[1].init_position(2, 0, 0);
	nose.init_rotate(90, 1, 0, 0); nose.init_position(0, 26.5, 2.5);

	head.init_scale(0.15);
	body.init_scale(0.15);
	nose.init_scale(0.15);
	for (int i = 0; i < 2; ++i) {	//哭率 坷弗率
		arm[i].init_scale(0.15);
		leg[i].init_scale(0.15);
	}
	rotation_angle = 0;
	rArm_out = true;
	plus_angle = 2;
	max_angle = 30;
	Arm_angle  = 0;
}

void Robot::Draw()
{
	head.Draw();
	body.Draw();
	nose.Draw();
	for (int i = 0; i < 2; ++i) {	//哭率 坷弗率
		arm[i].Draw();
		leg[i].Draw();
	}
}

void Robot::Move(int way)
{
	glm::vec3 w_vector = glm::normalize(glm::vec3(glm::cos(glm::radians(90 - rotation_angle)), 0, glm::sin(glm::radians(90 -rotation_angle))));
	w_vector.x = w_vector.x * speed;
	w_vector.y = w_vector.y * speed;
	w_vector.z = w_vector.z * speed;
	switch (way) {
	case 8:
		cur_loc += w_vector;
		break;
	case 2:
		cur_loc -= w_vector;
		break;
	}
	body.Move(cur_loc);
	head.Move(cur_loc);
	nose.Move(cur_loc);
	for (int i = 0; i < 2; ++i) {
		arm[i].Move(cur_loc);
		leg[i].Move(cur_loc);
	}
}

void Robot::Rotate(int way)
{
	switch (way) {
	case 4:
		rotation_angle += 5;
		if (rotation_angle >= 360)
			rotation_angle = 0;
		break;
	case 6:
		rotation_angle -= 5;
		if (rotation_angle <= -360)
			rotation_angle = 0;
		break;
	}
	body.Rotate(glm::vec3(rotation_angle, 0, 0));
	head.Rotate(glm::vec3(rotation_angle, 0, 0));
	nose.Rotate(glm::vec3(rotation_angle, 0, 0));
	for (int i = 0; i < 2; ++i) {
		arm[i].Rotate(glm::vec3(rotation_angle, 0, 0));
		leg[i].Rotate(glm::vec3(rotation_angle, 0, 0));
	}
}

void Robot::arm_legAni()
{
	if (rArm_out) {
		if (max_angle > Arm_angle) {
			Arm_angle += plus_angle;
			arm[0].swing(6, plus_angle);
			arm[1].swing(4, plus_angle);
			leg[0].swing(4, plus_angle);
			leg[1].swing(6, plus_angle);
			if (Arm_angle >= max_angle)
				rArm_out = false;
		}
	}
	else {
		if (-max_angle < Arm_angle) {
			Arm_angle -= plus_angle;
			arm[0].swing(4, plus_angle);
			arm[1].swing(6, plus_angle);
			leg[0].swing(6, plus_angle);
			leg[1].swing(4, plus_angle);
			if (Arm_angle <= -max_angle)
				rArm_out = true;
		}
	}
}

void Robot::stand_ani()
{
	if (-2 > Arm_angle) {
		Arm_angle += plus_angle;
		arm[0].swing(6, plus_angle);
		arm[1].swing(4, plus_angle);
		leg[0].swing(4, plus_angle);
		leg[1].swing(6, plus_angle);
	}
	else if (2 < Arm_angle) {
		Arm_angle -= plus_angle;
		arm[0].swing(4, plus_angle);
		arm[1].swing(6, plus_angle);
		leg[0].swing(6, plus_angle);
		leg[1].swing(4, plus_angle);
	}
}

void Robot::speed_control(char c)
{
	switch (c) {
	case '+':
		if (speed < 0.35) {
			speed += 0.05;
			plus_angle += 2;
			max_angle += 2;
		}
		break;
	case '-':
		if (speed > 0.15) {
			speed -= 0.05;
			plus_angle -= 2;
			max_angle -= 2;
		}
		break;
	}
}

glm::vec3 Robot::return_loc()
{
	return cur_loc;
}