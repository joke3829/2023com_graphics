#include "Projection.h"

class Wall {
public:
	void Initialize(GLuint*, float, float, float);
	void Move(glm::vec3);
	void Rotate();
	void Draw();
private:
	float coor[12]{};
	float color[12]{};

	GLuint VAO, VBO[2];
	GLuint* shader;

	glm::vec3 center;
	glm::vec3 rotation_angle;

	glm::mat4 modelTrans;
};