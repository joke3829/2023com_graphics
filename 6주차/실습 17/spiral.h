#include "Line.h"

class spiral {
	GLuint VAO, VBO[2];		// 2���� �����̷�
	float coor[600]{};
	float color[600]{};
	glm::mat4 FinalTransformMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 finalrotate;
	GLuint* shader;
public:
	spiral();
	~spiral();
	void Initialize(GLuint*, int);
	void Draw();
};