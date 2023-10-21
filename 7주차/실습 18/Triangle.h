
#include "Cube.h"

class Triangle {
	GLuint VAO, VBO[2];

	float coor[9]{};
	float color[9]{};

	bool fold;
	bool state_r;

	glm::mat4 FinalTransformMatrix;
	glm::mat4 transMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 first_rotate;

	float fold_size;
	float scale_size;			// 스케일 사이즈
	glm::vec3 rotate_rad;		// 각 축에 따른 회전 각
	glm::vec3 trans_dis;		// 이동 거리
	GLuint* shader;
public:
	Triangle();
	~Triangle();
	void Initialize(GLuint*);				// vao, vbo 등을 생성 및 초기화	생성자에 넣을것
	void Draw();			//그리기 함수
	void Update_rotate(float, float, float, float);
	void Update_trans(float, float, float);
	void Update_scale(float);
	void change_bfold(bool);
	void change_state(bool);
	void fold_poly();
};