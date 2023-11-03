
#include "Bucket.h"

class Poly {
public:
	Poly();
	Poly(GLuint*, int);
	Poly(GLuint*, std::vector<glm::vec3>, std::vector<glm::vec3>, glm::vec2, int);
	void setSpeed(float);
	void setView(bool);
	void Move(glm::vec2);
	glm::vec2 move_xy();
	void Draw();
	void Initialize();
	void deleteBuffer();
	float return_t();
	bool check_cut(glm::vec2, glm::vec2);
	glm::vec2 return_loc();
	std::vector<glm::vec3> return_L();
	std::vector<glm::vec3> return_R();
	std::vector<glm::vec3> return_color();
	bool check_put();
	void crash_check(const Bucket&);
	void Move(bool);
private:
	GLuint* shader;
	GLuint VAO, VBO[2];
	std::vector<glm::vec3> coor;
	std::vector<glm::vec3> color;
	std::vector<glm::vec3> vertex_list;		// ������ �������� ���� ����Ʈ
	glm::vec2 cur_loc;
	glm::mat4 modelTrans;
	
	glm::vec2 controlPos[3];			// �ŰԺ��� ��� ��Ʈ�� ����Ʈ
	float t;							// �ŰԺ��� t
	float r, g, b;
	float speed;						

	int place_cross[2]{};					// ���� ��ġ

	bool view_poly;

	bool init_check;
	bool cutting;
	bool put_bucket;					// �ٱ��� ��� ����
};