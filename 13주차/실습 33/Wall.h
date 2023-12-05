#include "Robot.h"

class Wall {
public:
	void Initialize(GLuint*, float, float, float, int);
	void Move(glm::vec3);
	void Rotate(float, glm::vec3);
	void Open(int);
	void Draw();
	bool crash_check(Robot);
	glm::vec3 reflect_vector(Robot);
private:
	float coor[12]{};
	float color[12]{};

	int door_num;

	GLuint VAO, VBO[2];
	GLuint* shader;

	float wall_r;
	glm::vec3 rot_angle;
	glm::vec3 center;
	float rotation_angle;

	glm::mat4 modelTrans;
};