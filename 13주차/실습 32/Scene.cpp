#include "Scene.h"

Scene_1::Scene_1()
{
	view_cube = true;
	cube = new Mesh("obj\\unwrap_cube.obj", "obj\\cube_unwrap.jpg", 1024, 1024);
	pyramid = new Mesh("obj\\unwrap_pyramid.obj", "obj\\pyramid_unwrap.jpg", 1024, 1024);
	backg = new Mesh("obj\\background.obj", "obj\\back.jpg", 1024, 1024);
	backg->init_scale(10);
	cube->init_scale(0.3);
	cube->setLoc(glm::vec3(0, -2, 10));
	pyramid->init_scale(0.3);
	pyramid->setLoc(glm::vec3(0, -2, 10));
}

Scene_1::~Scene_1()
{
	delete cube;
	delete pyramid;
}

void Scene_1::setView(char c)
{
	switch (c) {
	case 'c':
		view_cube = true;
		break;
	case 'p':
		view_cube = false;
		break;
	}
}

void Scene_1::back()
{
	cube->setRot(glm::vec2(0, 0));
	pyramid->setRot(glm::vec2(0, 0));
}

Mesh* Scene_1::getCube()
{
	return cube;
}

Mesh* Scene_1::getPyramid()
{
	return pyramid;
}

void Scene_1::Render()
{
	backg->Render();
	if (view_cube)
		cube->Render();
	else
		pyramid->Render();
}