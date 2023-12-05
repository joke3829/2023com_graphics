
#include "ShaderProgram.h"
#include "CameraObj.h"

// 디폴트 생성자
CameraObj::CameraObj() {
	Initialize();
}

// 카메라 초기화
void CameraObj::Initialize()
{
	for (bool& m : move_state)
		m = false;
	shader = ShaderProgram::getShader();
	camera_dis = 40;				// EYE - AT
	cameraEYE = glm::vec3(0, 0, 22);
	cameraUP = glm::vec3(0, 1, 0);
	// ========================!중요!=====================
	// x가 증가하면 AT이 내가 바라보는 방향에서 우측으로
	// x가 감소하면 왼쪽
	// y가 증가하면 위로
	// y가 감소하면 아래
	// 뭔소린지 모르겠으면 설명해달라 꼭 물어보기
	// !이 방법이 마음에 안들면 상의 후 변경!
	// ====================================================
	rotation_angle = glm::vec2(-90, 0);
	OutToShader();
}

// uniform에 넣어주는 함수, 요소가 바뀌면 꼭 실행해주자
void CameraObj::OutToShader()
{
	//회전 각과 AT에 따른 EYE를 구한다
	float xz_dis;
	xz_dis = fabs(camera_dis * glm::cos(glm::radians(rotation_angle.y)));

	cameraAT.x = cameraEYE.x + (xz_dis * glm::cos(glm::radians(rotation_angle.x)));
	cameraAT.y = cameraEYE.y + (camera_dis * glm::sin(glm::radians(rotation_angle.y)));
	cameraAT.z = cameraEYE.z + (xz_dis * glm::sin(glm::radians(rotation_angle.x)));

	viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::lookAt(cameraEYE, cameraAT, cameraUP);
	// VertexShader의 view 위치를 받아 넣기
	int uni = glGetUniformLocation(shader->s_program, "view");
	if (uni < 0)
		std::cout << "uniform 변수를 찾지 못했습니다!" << std::endl;
	glUniformMatrix4fv(uni, 1, GL_FALSE, &viewMatrix[0][0]);
	// FragmentShader의 카메라 위치 보내주기
	uni = glGetUniformLocation(shader->s_program, "viewPos");
	if (uni < 0)
		std::cout << "uniform 변수를 찾지 못했습니다!" << std::endl;
	glUniform3fv(uni, 1, glm::value_ptr(cameraEYE));		// 확인 필요
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