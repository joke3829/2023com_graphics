
#include "Planet.h"

class SolarSystem {
	Mesh sun;
	Planet planet[3];
	Move_Circle orbit[3];

	GLuint* shader;
public:
	void Initialize(GLuint*);
	void Draw();
	void anime();
	void change_solid(bool);
	void rotate_z(int);
};
