//===========================================================
// ProjObj.h
// ������ȯ�� �����ϴ� ���
//===========================================================
			   
#include "stdafx.h"
			   
class ShaderProgram;
class ProjObj {
public:
	ProjObj();
	void OutToShader();
	
	// �ʿ��ϸ� ���� �Լ� �߰�

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