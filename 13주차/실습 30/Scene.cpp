#include "Scene.h"

Scene_1::Scene_1()
{
	view_cube = true;
	cube = new Mesh("obj\\unwrap_cube.obj", "obj\\cube_unwrap.jpg", 1024, 1024);
	pyramid = new Mesh("obj\\unwrap_pyramid.obj", "obj\\pyramid_unwrap.jpg", 1024, 1024);
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
	if (view_cube)
		cube->Render();
	else
		pyramid->Render();
}