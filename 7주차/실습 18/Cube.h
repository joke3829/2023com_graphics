#include "Projection.h"

class Cube {
	Mesh poly[6];
	
	GLuint* shader;
public:
	Cube();
	~Cube();
	void Initialize(GLuint*);
	void Draw();
	void t_rotate();
	void f_rotate(bool);
	void s_move(bool);
	void b_scale(bool);
};