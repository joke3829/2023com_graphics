
#include "ShaderProgram.h"
#include "CameraObj.h"

// ����Ʈ ������
CameraObj::CameraObj() {
	Initialize();
}

// ī�޶� �ʱ�ȭ
void CameraObj::Initialize()
{
	for (bool& m : move_state)
		m = false;
	shader = ShaderProgram::getShader();
	camera_dis = 40;				// EYE - AT
	cameraEYE = glm::vec3(0, 0, 22);
	cameraUP = glm::vec3(0, 1, 0);
	// ========================!�߿�!=====================
	// x�� �����ϸ� AT�� ���� �ٶ󺸴� ���⿡�� ��������
	// x�� �����ϸ� ����
	// y�� �����ϸ� ����
	// y�� �����ϸ� �Ʒ�
	// ���Ҹ��� �𸣰����� �����ش޶� �� �����
	// !�� ����� ������ �ȵ�� ���� �� ����!
	// ====================================================
	rotation_angle = glm::vec2(-90, 0);
	OutToShader();
}

// uniform�� �־��ִ� �Լ�, ��Ұ� �ٲ�� �� ����������
void CameraObj::OutToShader()
{
	//ȸ�� ���� AT�� ���� EYE�� ���Ѵ�
	float xz_dis;
	xz_dis = fabs(camera_dis * glm::cos(glm::radians(rotation_angle.y)));

	cameraAT.x = cameraEYE.x + (xz_dis * glm::cos(glm::radians(rotation_angle.x)));
	cameraAT.y = cameraEYE.y + (camera_dis * glm::sin(glm::radians(rotation_angle.y)));
	cameraAT.z = cameraEYE.z + (xz_dis * glm::sin(glm::radians(rotation_angle.x)));

	viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::lookAt(cameraEYE, cameraAT, cameraUP);
	// VertexShader�� view ��ġ�� �޾� �ֱ�
	int uni = glGetUniformLocation(shader->s_program, "view");
	if (uni < 0)
		std::cout << "uniform ������ ã�� ���߽��ϴ�!" << std::endl;
	glUniformMatrix4fv(uni, 1, GL_FALSE, &viewMatrix[0][0]);
	// FragmentShader�� ī�޶� ��ġ �����ֱ�
	uni = glGetUniformLocation(shader->s_program, "viewPos");
	if (uni < 0)
		std::cout << "uniform ������ ã�� ���߽��ϴ�!" << std::endl;
	glUniform3fv(uni, 1, glm::value_ptr(cameraEYE));		// Ȯ�� �ʿ�
}

void CameraObj::setCameraEYE(glm::vec3 new_loc)
{
	cameraEYE = new_loc;
	OutToShader();
}

void CameraObj::setCameraAngle(glm::vec2 new_rot)
{
	rotation_angle = new_rot;
	OutToShader();
}

void CameraObj::setMoveState(char c, bool flag)
{
	switch (c) {
	case 'w':
		move_state[0] = flag;
		break;
	case 'a':
		move_state[1] = flag;
		break;
	case 's':
		move_state[2] = flag;
		break;
	case 'd':
		move_state[3] = flag;
		break;
	}
}

void CameraObj::camera_move()
{
	glm::vec3 way = glm::normalize(cameraAT - cameraEYE);
	glm::vec3 right = glm::cross(way, cameraUP);
	if (move_state[0] && move_state[1]) {
		way = glm::normalize(way - right);
		setCameraEYE(cameraEYE + ((way * 10.0f) / 60.0f));
	}
	else if (move_state[1] && move_state[2]) {
		way = glm::normalize(-way - right);
		setCameraEYE(cameraEYE + ((way * 10.0f) / 60.0f));
	}
	else if (move_state[2] && move_state[3]) {
		way = glm::normalize(-way + right);
		setCameraEYE(cameraEYE + ((way * 10.0f) / 60.0f));
	}
	else if (move_state[0] && move_state[3]) {
		way = glm::normalize(way + right);
		setCameraEYE(cameraEYE + ((way * 10.0f) / 60.0f));
	}
	else if (move_state[0]) {
		setCameraEYE(cameraEYE + ((way * 10.0f) / 60.0f));
	}
	else if (move_state[1]) {
		setCameraEYE(cameraEYE - ((right * 10.0f) / 60.0f));
	}
	else if (move_state[2]) {
		setCameraEYE(cameraEYE - ((way * 10.0f) / 60.0f));
	}
	else if (move_state[3]) {
		setCameraEYE(cameraEYE + ((right * 10.0f) / 60.0f));
	}
}

void CameraObj::update_angle(float dx, float dy)
{
	rotation_angle.x += dx;
	if (rotation_angle.x > 360)
		rotation_angle.x -= 360;
	if (rotation_angle.x < -360)
		rotation_angle += 360;

	rotation_angle.y += dy;
	if (rotation_angle.y > 90)
		rotation_angle.y = 89;
	if (rotation_angle.y < -90)
		rotation_angle.y = -89;
	OutToShader();
}