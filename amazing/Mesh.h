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
	Mesh(std::string);
	virtual ~Mesh();

	void Initialize(std::string);				// �ʱ�ȭ
	void F_Initalize();

	void init_scale(float);							// �ʱ� ������ ����
	void init_position(float, float, float);		// �ʱ� ��ġ ����
	void init_rotate(float, float, float, float);	// �ʱ� ȸ�� ����

	void setLoc(glm::vec3);							// ��ġ �ٲ��ֱ�
	void setRot(glm::vec2);							// ȸ���� �ٲ��ֱ�

	void setSpd(float);								// ��� ���ǵ� ����


	void anime_1();		// �ö�Դ� �����Դ�
	void anime_2();		// �ĵ�Ÿ��
	void anime_3();		// ?

	void back_scale();	// ������ �ʱ�ȭ

	void ready_ani_1();
	void ready_ani_2(int);		
	void ready_ani_3();

	void Render() const;
	void F_Render() const;

	static float frame_late;

protected:
	unsigned int triangle_num;
	GLuint VAO, VBO[3], EBO;
	// �ؽ��� �߰� ����
	std::vector<glm::vec3> vertexs;			// ����
	std::vector<glm::vec3> colors;			// �÷�(�Ƹ� ���� ����, �ؽ�ó)
	std::vector<glm::vec3> vertex_normal;	// �븻
	std::vector<unsigned int> index;



	glm::mat4 modelTrans;
	glm::mat4 rotateMatrix;		// �븻 ���͸� ������ ���� ���

	glm::vec3 init_pos;			// �ʱ� ��ġ ����
	glm::vec3 cur_loc;			// ���� ��ġ

	glm::vec3 init_rot;			// �ʱ� ȸ��
	glm::vec2 cur_rot;			// ���� ȸ����


	bool ReadOBJ(std::string);		// OBJ�о����
	ShaderProgram* shader;

private:
	bool upper;			// true�� ���
	bool moving;		// true�� ��������

	float scale_value;			// ���� �����
	float scale_spd;			// ������ �ӵ�
};