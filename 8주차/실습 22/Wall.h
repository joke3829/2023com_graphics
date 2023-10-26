#include "Robot.h"

class Wall {
public:
	void Initialize(GLuint*, float, float, float, int);
	void Move(glm::vec3);
	void Rotate(float, glm::vec3);
	void Open(int);
	void Draw();
	bool crash_check(const Robot&);
private:
	float coor[12]{};
	float color[12]{};

	int door_num;

	GLuint VAO, VBO[2];
	GLuint* shader;

	glm::vec3 center;
	float rotation_angle;

	glm::mat4 modelTrans;
};