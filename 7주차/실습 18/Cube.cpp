#include "Cube.h"

Cube::Cube() 
{
}

Cube::~Cube()
{
}

void Cube::Initialize(GLuint* shaderProgram)
{
	shader = shaderProgram;
	for (Mesh& p : poly) {	// bottom, left,front, right, back, top
		p.Initialize(shader);
		p.Update_scale(1.5);
	}
	poly[0].Update_rotate(90, 1, 0, 0); poly[0].Update_trans(0, -1.5, 0);
	poly[1].Update_rotate(-90, 0, 1, 0); poly[1].Update_trans(-1.5, 0, 0);
	poly[2].Update_first();  poly[2].Update_trans(0, -1.5, 1.5);
	poly[3].Update_rotate(90, 0, 1, 0); poly[3].Update_trans(1.5, 0, 0);
	poly[4].Update_rotate(180, 0, 1, 0); poly[4].Update_trans(0, 0, -1.5);
	poly[5].Update_rotate(-90, 1, 0, 0); poly[5].Update_trans(0, 1.5, 0);
}

void Cube::Draw()
{
	for (Mesh p : poly)
		p.Draw();
}

void Cube::t_rotate()
{
	poly[5].t_rotate();
}

void Cube::f_rotate(bool flag)
{
	poly[2].f_rotate(flag);
}

void Cube::s_move(bool flag)
{
	poly[1].s_move(flag);
	poly[3].s_move(flag);
}

void Cube::b_scale(bool flag)
{
	poly[4].b_scale(flag);
}