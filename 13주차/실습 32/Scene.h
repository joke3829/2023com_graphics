#pragma once
#include "stdafx.h"
#include "Mesh.h"
class Scene_1 {
public:
	Scene_1();
	~Scene_1();

	void setView(char);
	void back();

	Mesh* getCube();
	Mesh* getPyramid();

	void Render();
private:
	bool view_cube;

	Mesh* cube;
	Mesh* pyramid;
	Mesh* backg;
};