#include "Triangle.h"

class Pyramid {
	Mesh bottom;
	Triangle tri[4];

	GLuint* shader;
public:
	Pyramid();
	~Pyramid();
	void Initialize(GLuint*);
	void Draw();
	void change_tri_bool(bool);
	void fold_timer();
	void change_tri_state(bool);
	void change_tri_bool(bool, int);
};