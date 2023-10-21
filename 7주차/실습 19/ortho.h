
#include "Solar_System.h"

class Ortho {
	GLuint* shader;
	glm::mat4 proj;
public:
	void Initialize(GLuint*);
	void OuttoVS();
};