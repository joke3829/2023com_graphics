
#include "KeyboardFunc.h"
#include "CameraObj.h"


KeyboardFunc::KeyboardFunc(CameraObj* t_camera, Scene_1* ss)
	: mCamera(t_camera), scene(ss)
{
}

void KeyboardFunc::Keyboard(unsigned char key, int x, int y)
{
	glm::vec2 temp;
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'x':
		temp = scene->getCube()->getRot();
		temp.x += 5;
		scene->getCube()->setRot(temp);

		temp = scene->getPyramid()->getRot();
		temp.x += 5;
		scene->getPyramid()->setRot(temp);
		break;
	case 'X':
		temp = scene->getCube()->getRot();
		temp.x -= 5;
		scene->getCube()->setRot(temp);

		temp = scene->getPyramid()->getRot();
		temp.x -= 5;
		scene->getPyramid()->setRot(temp);
		break;
	case 'y':
		temp = scene->getCube()->getRot();
		temp.y += 5;
		scene->getCube()->setRot(temp);

		temp = scene->getPyramid()->getRot();
		temp.y += 5;
		scene->getPyramid()->setRot(temp);
		break;
	case 'Y':
		temp = scene->getCube()->getRot();
		temp.y -= 5;
		scene->getCube()->setRot(temp);

		temp = scene->getPyramid()->getRot();
		temp.y -= 5;
		scene->getPyramid()->setRot(temp);
		break;
	case 'c':
		scene->setView('c');
		break;
	case 'p':
		scene->setView('p');
		break;
	case 's':
		scene->back();
		break;
	}
	glutPostRedisplay();		// ???
}

void KeyboardFunc::KeyboardUp(unsigned char key, int x, int y)
{
	switch (key) {
	}
	glutPostRedisplay();		// ???
}