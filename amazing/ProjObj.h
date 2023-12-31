//===========================================================
// ProjObj.h
// 투영변환을 관리하는 헤더
//===========================================================
			   
#include "stdafx.h"
			   
class ShaderProgram;
class ProjObj {
public:
	ProjObj();
	void OutToShader();
	
	// 필요하면 변경 함수 추가

protected:
private:
	ShaderProgram* shader;
	float fovy;
	float aspect;
	float n;
	float f;

	glm::mat4 ProjMatrix;

	void Initialize();
};

class OrtObj {
public:
	OrtObj();
	void OutToShader();
private:
	ShaderProgram* shader;
	glm::mat4 ProjMatrix;

};