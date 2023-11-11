
#include "Mesh.h"

class Camera {
	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::mat4 view;
	glm::vec2 rotation_angle;
	float camera_dis;

	GLuint* shader;
public:
	Camera();
	~Camera();
	void Initialize(GLuint*);
	void UpdateCamera(float, float, float);
	void Control_camera(glm::vec3, glm::vec3);
	void Control_init();
	void OuttoVS();
	void Vertical_Move(int);
	void Direcion_Move(int);
	void Move(int);
	void Pos_update(glm::vec3);
	void dis_plus(int);
	void rotate_pos(int);
};