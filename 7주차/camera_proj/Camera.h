
#include "Line.h"

class Camera {
	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::mat4 view;

	GLuint* shader;
public:
	Camera();
	~Camera();
	void Initialize(GLuint*);
	void Update_camera(glm::vec3, glm::vec3, glm::vec3);
	void OuttoVS();
};