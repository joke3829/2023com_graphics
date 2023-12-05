#include "Wall.h"

void Wall::Initialize(GLuint* shaderProgram, float r, float g, float b, int type)
{
	door_num = type;
	shader = shaderProgram;
	if (type == 0) {
		coor[0] = -10; coor[1] = 10;
		coor[3] = -10; coor[4] = -10;
		coor[6] = 10; coor[7] = -10;
		coor[9] = 10; coor[10] = 10;
	}
	else if (type == 1 || type == 2) {
		coor[0] = -5; coor[1] = 10;
		coor[3] = -5; coor[4] = -10;
		coor[6] = 5; coor[7] = -10;
		coor[9] = 5; coor[10] = 10;
	}

	color[0] = color[3] = color[6] = color[9] = r;
	color[1] = color[4] = color[7] = color[10] = g;
	color[2] = color[5] = color[8] = color[11] = b;

	center = rot_angle = glm::vec3(0, 0, 0);
	rotation_angle = 0;
	wall_r = 10;

	modelTrans = glm::mat4(1.0f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coor), coor, GL_STATIC_DRAW);
	unsigned int loc = glGetAttribLocation(*shader, "vPos");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	loc = glGetAttribLocation(*shader, "vColor");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);
}

void Wall::Draw()
{
	int uni = glGetUniformLocation(*shader, "transform");
	glUniformMatrix4fv(uni, 1, GL_FALSE, glm::value_ptr(modelTrans));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Wall::Rotate(float rad, glm::vec3 axis)
{
	if (axis.x == 1)
		rot_angle.x += rad;
	if (axis.y == 1)
		rot_angle.y += rad;
	if (axis.z == 1)
		rot_angle.z += rad;
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::rotate(temp, glm::radians(rad), axis) * modelTrans;
}

void Wall::Move(glm::vec3 new_loc)
{
	center = new_loc;
	glm::mat4 temp = glm::mat4(1.0f);
	modelTrans = glm::translate(temp, center) * modelTrans;
}

void Wall::Open(int way) {
	glm::mat4 temp = glm::mat4(1.0f);
	if (door_num == 1) {		//왼쪽 문
		modelTrans = glm::translate(temp, -center) * modelTrans; temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(5, 0, 0)) * modelTrans; temp = glm::mat4(1.0f);
		switch (way) {
		case 4:	// 열림
			if (rotation_angle < 100) {
				rotation_angle += 5;
				modelTrans = glm::rotate(temp, glm::radians(-5.0f), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);

			}
			break;
		case 6: // 닫힘
			if (rotation_angle > 0) {
				rotation_angle -= 5;
				modelTrans = glm::rotate(temp, glm::radians(5.0f), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);
			}
			break;
		}
		modelTrans = glm::translate(temp, center) * modelTrans; temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(-5, 0, 0)) * modelTrans; temp = glm::mat4(1.0f);
	}
	else if (door_num == 2) {	// 오른쪽문
		modelTrans = glm::translate(temp, -center) * modelTrans; temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(-5, 0, 0)) * modelTrans; temp = glm::mat4(1.0f);
		switch (way) {
		case 4:	// 열림
			if (rotation_angle < 100) {
				rotation_angle += 5;
				modelTrans = glm::rotate(temp, glm::radians(5.0f), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);

			}
			break;
		case 6: // 닫힘
			if (rotation_angle > 0) {
				rotation_angle -= 5;
				modelTrans = glm::rotate(temp, glm::radians(-5.0f), glm::vec3(0, 1, 0)) * modelTrans; temp = glm::mat4(1.0f);
			}
			break;
		}
		modelTrans = glm::translate(temp, center) * modelTrans; temp = glm::mat4(1.0f);
		modelTrans = glm::translate(temp, glm::vec3(5, 0, 0)) * modelTrans; temp = glm::mat4(1.0f);
	}
}

bool Wall::crash_check(Robot t_robot)
{
	glm::vec3 LB(center.x - wall_r, center.y - wall_r, center.z);
	glm::vec3 RT(center.x + wall_r, center.y + wall_r, center.z + 5);
	glm::mat4 temp(1.0f);
	temp = glm::translate(temp, -center);
	LB = temp * glm::vec4(LB, 1); RT = temp * glm::vec4(RT, 1); temp = glm::mat4(1.0f);
	if (rot_angle.x != 0)
		temp = glm::rotate(temp, glm::radians(rot_angle.x), glm::vec3(1, 0, 0));
	else if(rot_angle.y != 0)
		temp = glm::rotate(temp, glm::radians(rot_angle.y), glm::vec3(0, 1, 0));
	else if(rot_angle.z != 0)
		temp = glm::rotate(temp, glm::radians(rot_angle.z), glm::vec3(0, 0, 1));
	LB = temp * glm::vec4(LB, 1); RT = temp * glm::vec4(RT, 1); temp = glm::mat4(1.0f);
	temp = glm::translate(temp, center);
	LB = temp * glm::vec4(LB, 1); RT = temp * glm::vec4(RT, 1); temp = glm::mat4(1.0f);
	
	glm::vec3 min; glm::vec3 max;
	if (LB.x > RT.x) {
		min.x = RT.x;
		max.x = LB.x;
	}
	else {
		min.x = LB.x;
		max.x = RT.x;
	}
	if (LB.y > RT.y) {
		min.y = RT.y;
		max.y = LB.y;
	}
	else {
		min.y = LB.y;
		max.y = RT.y;
	}
	if (LB.z > RT.z) {
		min.z = RT.z;
		max.z = LB.z;
	}
	else {
		min.z = LB.z;
		max.z = RT.z;
	}

	// 충돌 확인
	// 왼쪽 위 점
	if (min.x <= t_robot.return_loc().x - 0.6 && max.x >= t_robot.return_loc().x - 0.6 &&
		min.y <= t_robot.return_loc().y + 0.01 && max.y >= t_robot.return_loc().y + 0.01 &&
		min.z <= t_robot.return_loc().z - 0.6 && max.z >= t_robot.return_loc().z - 0.6)
		return true;
	// 왼쪽 아래 점
	if (min.x <= t_robot.return_loc().x - 0.6 && max.x >= t_robot.return_loc().x - 0.6 &&
		min.y <= t_robot.return_loc().y + 0.01 && max.y >= t_robot.return_loc().y + 0.01 &&
		min.z <= t_robot.return_loc().z + 0.6 && max.z >= t_robot.return_loc().z + 0.6)
		return true;
	// 오른쪽 아래 점
	if (min.x <= t_robot.return_loc().x + 0.6 && max.x >= t_robot.return_loc().x + 0.6 &&
		min.y <= t_robot.return_loc().y + 0.01 && max.y >= t_robot.return_loc().y + 0.01 &&
		min.z <= t_robot.return_loc().z + 0.6 && max.z >= t_robot.return_loc().z + 0.6)
		return true;
	// 오른쪽 위 점
	if (min.x <= t_robot.return_loc().x + 0.6 && max.x >= t_robot.return_loc().x + 0.6 &&
		min.y <= t_robot.return_loc().y + 0.01 && max.y >= t_robot.return_loc().y + 0.01 &&
		min.z <= t_robot.return_loc().z - 0.6 && max.z >= t_robot.return_loc().z - 0.6)
		return true;

	/*std::cout << t_robot.return_loc().x << " " << t_robot.return_loc().y << " " << t_robot.return_loc().z << std::endl;
	std::cout << min.x << " " << min.y << " " << min.z << std::endl;
	std::cout << max.x << " " << max.y << " " << max.z << std::endl;*/
	return false;
}

glm::vec3 Wall::reflect_vector(Robot t_robot)
{
	glm::vec3 l_vector = glm::normalize(glm::vec3(glm::cos(glm::radians(90 - t_robot.return_rot())), 0, glm::sin(glm::radians(90 - t_robot.return_rot()))));
	glm::vec3 w_normal(0, 0, -1);
	glm::mat4 temp(1.0f);
	if (rot_angle.x != 0)
		temp = glm::rotate(temp, glm::radians(rot_angle.x), glm::vec3(1, 0, 0));
	else if (rot_angle.y != 0)
		temp = glm::rotate(temp, glm::radians(rot_angle.y), glm::vec3(0, 1, 0));
	else if (rot_angle.z != 0)
		temp = glm::rotate(temp, glm::radians(rot_angle.z), glm::vec3(0, 0, 1));
	w_normal = temp * glm::vec4(w_normal, 1);
	std::cout << glm::reflect(glm::normalize(l_vector), glm::normalize(w_normal)).x << " " << glm::reflect(glm::normalize(l_vector), glm::normalize(w_normal)).y << " " << glm::reflect(glm::normalize(l_vector), glm::normalize(w_normal)).z << std::endl;
	return glm::reflect(glm::normalize(l_vector), glm::normalize(w_normal));
}
