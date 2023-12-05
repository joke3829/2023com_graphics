//============================================================
// Mesh.h
// �޽� ��� �� ���� ���
// ��� ���� ���� ��ȯ �������
//============================================================
#pragma once
#include "stdafx.h"

class ShaderProgram;
class Mesh {
public:
	Mesh();
	Mesh(std::string, std::string, int, int);
	virtual ~Mesh();

	void Initialize(std::string);				// �ʱ�ȭ
	void Init_texture(std::string, int, int);

	void init_scale(float);							// �ʱ� ������ ����
	void init_position(float, float, float);		// �ʱ� ��ġ ����
	void init_rotate(float, float, float, float);	// �ʱ� ȸ�� ����

	void setLoc(glm::vec3);							// ��ġ �ٲ��ֱ�
	void setRot(glm::vec2);							// ȸ���� �ٲ��ֱ�

	glm::vec2 getRot() const;

	void Render() const;

	static float frame_late;

protected:
	//unsigned int vertex_num;
	GLuint VAO, VBO[3];
	unsigned int texture;
	
	std::vector<glm::vec3> vertexs;			// ����
	std::vector<glm::vec3> texture_coor;	// �ؽ��� ��ǥ
	std::vector<glm::vec3> vertex_normal;	// �븻
	//std::vector<unsigned int> index;



	glm::mat4 modelTrans;
	glm::mat4 rotateMatrix;		// �븻 ���͸� ������ ���� ���

	glm::vec3 init_pos;			// �ʱ� ��ġ ����
	glm::vec3 cur_loc;			// ���� ��ġ

	glm::vec3 init_rot;			// �ʱ� ȸ��
	glm::vec2 cur_rot;			// ���� ȸ����


	bool ReadOBJ(std::string);		// OBJ�о����
	ShaderProgram* shader;

private:
};