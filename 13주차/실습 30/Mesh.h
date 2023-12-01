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
	Mesh(std::string, std::string, int, int);
	virtual ~Mesh();

	void Initialize(std::string);				// 초기화
	void Init_texture(std::string, int, int);

	void init_scale(float);							// 초기 스케일 조정
	void init_position(float, float, float);		// 초기 위치 설정
	void init_rotate(float, float, float, float);	// 초기 회전 설정

	void setLoc(glm::vec3);							// 위치 바꿔주기
	void setRot(glm::vec2);							// 회전율 바꿔주기

	glm::vec2 getRot() const;

	void Render() const;

	static float frame_late;

protected:
	//unsigned int vertex_num;
	GLuint VAO, VBO[3];
	unsigned int texture;
	
	std::vector<glm::vec3> vertexs;			// 정점
	std::vector<glm::vec3> texture_coor;	// 텍스쳐 좌표
	std::vector<glm::vec3> vertex_normal;	// 노말
	//std::vector<unsigned int> index;



	glm::mat4 modelTrans;
	glm::mat4 rotateMatrix;		// 노말 벡터를 돌리기 위한 행렬

	glm::vec3 init_pos;			// 초기 위치 지정
	glm::vec3 cur_loc;			// 현재 위치

	glm::vec3 init_rot;			// 초기 회전
	glm::vec2 cur_rot;			// 현재 회전각


	bool ReadOBJ(std::string);		// OBJ읽어오기
	ShaderProgram* shader;

private:
};