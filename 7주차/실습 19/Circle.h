
#include "Projection.h"

class Move_Circle {
	GLuint* shader;
	GLuint VAO, VBO[2];

	glm::mat4 modelTrans;
	glm::mat4 scaleMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 finalMat;
	float coor[1080]{};
	float color[1080]{};
	glm::vec3 move_dis;
public:
	Move_Circle();
	~Move_Circle();
	void Initialize(GLuint*, float);
	void Draw();
	void Move(float, float, float);
	void decide(glm::mat4);
	void decide(float, float, float, float);
};