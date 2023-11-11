#include "Robot.h"

void Robot::Initialize(GLuint* shaderProgram)
{
	speed = 0.1;
	shader = shaderProgram;
	head.Initialize(shader, "robot\\head.obj");
	nose.Initialize(shader, "robot\\nose.obj");
	body.Initialize(shader, "robot\\body.obj");
	for (int i = 0; i < 2; ++i) {	//왼쪽 오른쪽
		arm[i].Initialize(shader, "robot\\arm_leg.obj");
		leg[i].Initialize(shader, "robot\\arm_leg.obj");
	}
	head.init_position(0, 24, 0);
	body.init_position(0, 12, 0);
	arm[0].init_position(-6, 12, 0); arm[1].init_position(6, 12, 0);
	leg[0].init_position(-2, 0, 0); leg[1].init_position(2, 0, 0);
	nose.init_rotate(90, 1, 0, 0); nose.init_position(0, 26.5, 2.5);

	head.init_scale(0.1);
	body.init_scale(0.1);
	nose.init_scale(0.1);
	for (int i = 0; i < 2; ++i) {	//왼쪽 오른쪽
		arm[i].init_scale(0.1);
		leg[i].init_scale(0.1);
	}
	rotation_angle = 0;
	rArm_out = true;
	plus_angle = 2;
	max_angle = 30;
	Arm_angle  = 0;
	live = true;
}

void Robot::Draw()
{
	head.Draw();
	body.Draw();
	nose.Draw();
	for (int i = 0; i < 2; ++i) {	//왼쪽 오른쪽
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
			rotation_angle -= 360;
		break;
	case 6:
		rotation_angle -= 5;
		if (rotation_angle <= -360)
			rotation_angle += 360;
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

float Robot::return_rot()
{
	return rotation_angle;
}

void Robot::angle_change(glm::vec3 r_vector)
{
	glm::vec3 w_vector = glm::normalize(glm::vec3(glm::cos(glm::radians(90 - rotation_angle)), 0, glm::sin(glm::radians(90 - rotation_angle))));	// 바라보는 방향 벡터
	float angle = glm::acos(glm::dot(glm::normalize(w_vector), glm::normalize(r_vector))) * 180.0f / glm::pi<float>();
	std::cout << "rotation_angle: " << rotation_angle << std::endl;
	int temp_angle = rotation_angle + 1080;
	temp_angle %= 360;
	std::cout << "temp_angle: " << temp_angle << std::endl;
	if (temp_angle <= 45)
		if (angle <= 90)
			rotation_angle -= angle;
		else
			rotation_angle += angle;
	else if (temp_angle <= 90)
		if (angle <= 90)
			rotation_angle += angle;
		else
			rotation_angle -= angle;
	else if (temp_angle <= 135)
		if (angle <= 90)
			rotation_angle -= angle;
		else
			rotation_angle += angle;
	else if (temp_angle <= 180)
		if (angle <= 90)
			rotation_angle += angle;
		else
			rotation_angle -= angle;
	else if (temp_angle <= 225)
		if (angle <= 90)
			rotation_angle -= angle;
		else
			rotation_angle += angle;
	else if (temp_angle <= 270)
		if (angle <= 90)
			rotation_angle += angle;
		else
			rotation_angle -= angle;
	else if (temp_angle <= 315)
		if (angle <= 90)
			rotation_angle -= angle;
		else
			rotation_angle += angle;
	else if (temp_angle <= 360)
		if (angle <= 90)
			rotation_angle += angle;
		else
			rotation_angle -= angle;


	if (rotation_angle >= 360)
		rotation_angle -= 360;
	else if(rotation_angle <= -360)
		rotation_angle += 360;
	std::cout << "변경 후 : " << rotation_angle << std::endl;
	body.Rotate(glm::vec3(rotation_angle, 0, 0));
	head.Rotate(glm::vec3(rotation_angle, 0, 0));
	nose.Rotate(glm::vec3(rotation_angle, 0, 0));
	for (int i = 0; i < 2; ++i) {
		arm[i].Rotate(glm::vec3(rotation_angle, 0, 0));
		leg[i].Rotate(glm::vec3(rotation_angle, 0, 0));
	}
}

void Robot::fallen(int way)
{
	glm::vec3 d_way;
	switch (way) {
	case 8:		// 올라가
		d_way = glm::vec3(0, 1, 0);
		break;
	case 5:		// 가지마
		d_way = glm::vec3(0, 0.5, 0);
		break;
	case 2:		// 내려가
		d_way = glm::vec3(0, -0.5, 0);
		break;
	}
	cur_loc += d_way;
	body.Move(cur_loc);
	head.Move(cur_loc);
	nose.Move(cur_loc);
	for (int i = 0; i < 2; ++i) {
		arm[i].Move(cur_loc);
		leg[i].Move(cur_loc);
	}
}

bool Robot::check_crash(Mesh obs)
{
	std::vector<glm::vec3> obs_ver = obs.return_vertex();
	glm::vec3 min; glm::vec3 max;
	min = obs_ver[0]; max = obs_ver[0];
	for (int i = 1; i < obs_ver.size(); ++i) {
		if (min.x > obs_ver[i].x)
			min.x = obs_ver[i].x;
		if (min.y > obs_ver[i].y)
			min.y = obs_ver[i].y;
		if (min.z > obs_ver[i].z)
			min.z = obs_ver[i].z;
		if (max.x < obs_ver[i].x)
			max.x = obs_ver[i].x;
		if (max.y < obs_ver[i].y)
			max.y = obs_ver[i].y;
		if (max.z < obs_ver[i].z)
			max.z = obs_ver[i].z;
	}
	// ======================= 크기 수정하자
	min *= 0.2;		
	max *= 0.2;
	// =======================
	min += obs.return_loc();
	max += obs.return_loc();
	if (min.x <= cur_loc.x - 0.4 && max.x >= cur_loc.x - 0.4 &&
		min.y <= cur_loc.y + 0.01 && max.y >= cur_loc.y + 0.01 &&
		min.z <= cur_loc.z - 0.4 && max.z >= cur_loc.z - 0.4)
		return true;
	// 왼쪽 아래 점
	if (min.x <= cur_loc.x - 0.4 && max.x >= cur_loc.x - 0.4 &&
		min.y <= cur_loc.y + 0.01 && max.y >= cur_loc.y + 0.01 &&
		min.z <= cur_loc.z + 0.4 && max.z >= cur_loc.z + 0.4)
		return true;
	// 오른쪽 아래 점
	if (min.x <= cur_loc.x + 0.4 && max.x >= cur_loc.x + 0.4 &&
		min.y <= cur_loc.y + 0.01 && max.y >= cur_loc.y + 0.01 &&
		min.z <= cur_loc.z + 0.4 && max.z >= cur_loc.z + 0.4)
		return true;
	// 오른쪽 위 점
	if (min.x <= cur_loc.x + 0.4 && max.x >= cur_loc.x + 0.4 &&
		min.y <= cur_loc.y + 0.01 && max.y >= cur_loc.y + 0.01 &&
		min.z <= cur_loc.z - 0.4 && max.z >= cur_loc.z - 0.4)
		return true;

	return false;
}

bool Robot::check_crash(Robot enemy)
{
	glm::vec3 min; glm::vec3 max;
	min.x = enemy.return_loc().x - 1;
	min.y = enemy.return_loc().y + 3.35;
	min.z = enemy.return_loc().z - 1;
	max.x = enemy.return_loc().x + 1;
	max.y = enemy.return_loc().y + 4.35;
	max.z = enemy.return_loc().z + 1;

	if (min.x <= cur_loc.x && max.x >= cur_loc.x &&
		min.y <= cur_loc.y && max.y >= cur_loc.y &&
		min.z <= cur_loc.z && max.z >= cur_loc.z)
		return true;

	return false;
}

void Robot::Trans_init(glm::vec3 new_loc)
{
	if (not live) {
		body.death(8);
		head.death(8);
		nose.death(8);
		for (int i = 0; i < 2; ++i) {
			arm[i].death(8);
			leg[i].death(8);
		}
	}
	cur_loc = new_loc;
	rotation_angle = 0;
	body.Move(cur_loc);
	head.Move(cur_loc);
	nose.Move(cur_loc);
	for (int i = 0; i < 2; ++i) {
		arm[i].Move(cur_loc);
		leg[i].Move(cur_loc);
	}
	body.Rotate(glm::vec3(rotation_angle, 0, 0));
	head.Rotate(glm::vec3(rotation_angle, 0, 0));
	nose.Rotate(glm::vec3(rotation_angle, 0, 0));
	for (int i = 0; i < 2; ++i) {
		arm[i].Rotate(glm::vec3(rotation_angle, 0, 0));
		leg[i].Rotate(glm::vec3(rotation_angle, 0, 0));
	}
	live = true;
}

void Robot::death()
{
	if (live) {
		body.death(2);
		head.death(2);
		nose.death(2);
		for (int i = 0; i < 2; ++i) {
			arm[i].death(2);
			leg[i].death(2);
		}
	}
	live = false;
}

bool Robot::state_check()
{
	return live;
}