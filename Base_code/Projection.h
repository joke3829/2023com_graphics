#include "Camera.h"

class Projection {
	float fovy;
	float aspect;
	float n;
	float f;

	glm::mat4 proj;

	GLuint* shader;
public:
	Projection();
	~Projection();
	void Initialize(GLuint*);
	void Update_Proj(float, float, float, float);
	void OuttoVS();
};