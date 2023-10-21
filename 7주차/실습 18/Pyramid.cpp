#include "Pyramid.h"

Pyramid::Pyramid()
{}

Pyramid::~Pyramid()
{}

void Pyramid::Initialize(GLuint* shaderProgram)
{
	shader = shaderProgram;
	bottom.Initialize(shader);
	bottom.Update_scale(1.5);
	for (Triangle& t : tri) {	// left front right back
		t.Initialize(shader);
		t.Update_scale(1.5);
	}
	bottom.Update_rotate(90, 1, 0, 0);
	tri[0].Update_rotate(-90, 0, 1, 0); tri[0].Update_trans(-1.5, 0, 0);
	tri[1].Update_trans(0, 0, 1.5);
	tri[2].Update_rotate(90, 0, 1, 0); tri[2].Update_trans(1.5, 0, 0);
	tri[3].Update_rotate(180, 0, 1, 0); tri[3].Update_trans(0, 0, -1.5);
}

void Pyramid::Draw()
{
	bottom.Draw();
	for (Triangle t : tri)
		t.Draw();
}

void Pyramid::fold_timer()
{
	for (Triangle& t : tri)
		t.fold_poly();
}

void Pyramid::change_tri_bool(bool flag)
{
	for (Triangle& t : tri)
		t.change_bfold(flag);
}

void Pyramid::change_tri_state(bool flag)
{
	for (Triangle& t : tri)
		t.change_state(flag);
}

void Pyramid::change_tri_bool(bool flag, int index)
{
	tri[index].change_bfold(flag);
}