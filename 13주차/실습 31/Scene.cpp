#include "Scene.h"

Scene_1::Scene_1()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd(-20, 20);
	std::uniform_real_distribution<float> spd(5.0, 10.0);

	snowing = false;
	pyramid = new Mesh("obj\\pyramid.obj", "obj\\pyramid_basecolor.jpg", 1024, 1024);
	pyramid->set_ual(1.0f);
	bottom = new Mesh("obj\\bottom.obj", "obj\\snow_basecolor.jpg", 1024, 1024);
	bottom->set_ual(1.0f);
	buildings = new Mesh[5];
	snows = new Mesh[50];

	for (int i = 0; i < 5; ++i) {
		buildings[i].Initialize("obj\\building.obj");
		buildings[i].Init_texture("obj\\building_basecolor.jpg", 1024, 1024);
		buildings[i].set_ual(0.5f);
		buildings[i].init_position(urd(dre), 0, urd(dre));
	}

	for (int i = 0; i < 50; ++i) {
		snows[i].Initialize("obj\\snow.obj");
		snows[i].Init_texture("obj\\snow_basecolor.jpg", 1024, 1024);
		snows[i].set_ual(1.0f);
		snows[i].setLoc(glm::vec3(urd(dre), 30, urd(dre)));
		snows[i].setSpd(spd(dre));
	}
}

Scene_1::~Scene_1()
{
	delete pyramid;
	delete bottom;
	delete[] buildings;
	delete[] snows;
}

Mesh* Scene_1::getPyramid()
{
	return pyramid;
}

Mesh* Scene_1::getSnow()
{
	return snows;
}

void Scene_1::Render()
{
	bottom->Render();
	pyramid->Render();
	if (snowing) {
		for (int i = 0; i < 50; ++i)
			snows[i].Render();
	}
	for (int i = 0; i < 5; ++i)
		buildings[i].Render();
}

void Scene_1::s_ani()
{
	if (snowing) {
		for (int i = 0; i < 50; ++i) {
			glm::vec3 tt = snows[i].getLoc();
			tt.y -= snows[i].getSpd() / 60.0f;
			if (tt.y < 0)
				tt.y = 30;
			snows[i].setLoc(tt);
		}
	}
}

void Scene_1::s_switch()
{
	if (snowing)
		snowing = false;
	else
		snowing = true;
}