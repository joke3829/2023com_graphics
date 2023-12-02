#pragma once
#include "stdafx.h"
#include "Mesh.h"
class Scene_1 {
public:
	Scene_1();
	~Scene_1();

	void s_ani();
	void s_switch();

	Mesh* getPyramid();
	Mesh* getSnow();

	void Render();
private:
	bool snowing;
	Mesh* bottom;
	Mesh* pyramid;
	Mesh* buildings;
	Mesh* snows;
};