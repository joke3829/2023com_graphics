//============================================================
// Mesh.h
// 메쉬 출력 맟 관리 헤더
// 상속 시켜 각자 변환 사용하자
//============================================================
#pragma once
#include "stdafx.h"

class ShaderProgram;
class Mesh {
public:
	Mesh();
	Mesh(std::string);
	virtual ~Mesh();

	void Initialize(std::string);				// 초기화
	void F_Initalize();

	void init_scale(float);							// 초기 스케일 조정
	void init_position(float, float, float);		// 초기 위치 설정
	void init_rotate(float, float, float, float);	// 초기 회전 설정

	void setLoc(glm::vec3);							// 위치 바꿔주기
	void setRot(glm::vec2);							// 회전율 바꿔주기

	void setSpd(float);								// 상승 스피드 설정


	void anime_1();		// 올라왔다 내려왔다
	void anime_2();		// 파도타기
	void anime_3();		// ?

	void back_scale();	// 스케일 초기화

	void ready_ani_1();
	void ready_ani_2(int);		
	void ready_ani_3();

	void Render() const;
	void F_Render() const;

	static float frame_late;

protected:
	unsigned int triangle_num;
	GLuint VAO, VBO[3], EBO;
	// 텍스쳐 추가 예정
	std::vector<glm::vec3> vertexs;			// 정점
	std::vector<glm::vec3> colors;			// 컬러(아마 삭제 예상, 텍스처)
	std::vector<glm::vec3> vertex_normal;	// 노말
	std::vector<unsigned int> index;



	glm::mat4 modelTrans;
	glm::mat4 rotateMatrix;		// 노말 벡터를 돌리기 위한 행렬

	glm::vec3 init_pos;			// 초기 위치 지정
	glm::vec3 cur_loc;			// 현재 위치

	glm::vec3 init_rot;			// 초기 회전
	glm::vec2 cur_rot;			// 현재 회전각


	bool ReadOBJ(std::string);		// OBJ읽어오기
	ShaderProgram* shader;

private:
	bool upper;			// true면 상승
	bool moving;		// true면 움직여라

	float scale_value;			// 현재 신축률
	float scale_spd;			// 스케일 속도
};