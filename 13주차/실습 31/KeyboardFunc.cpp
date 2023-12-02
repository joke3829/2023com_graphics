
#include "KeyboardFunc.h"
#include "CameraObj.h"


KeyboardFunc::KeyboardFunc(CameraObj* t_camera, Scene_1* ss, LightObj* t_light)
	: mCamera(t_camera), scene(ss), light(t_light)
{
}

void KeyboardFunc::Keyboard(unsigned char key, int x, int y)
{
	glm::vec2 temp;
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'w':
		mCamera[0].setMoveState('w', true);
		break;
	case 'a':
		mCamera[0].setMoveState('a', true);
		break;
	case 's':
		mCamera[0].setMoveState('s', true);
		break;
	case 'd':
		mCamera[0].setMoveState('d', true);
		break;
	case 'm':
		light->lightButton();
		break;
	case 'f':
		scene->s_switch();
		break;
	}
	glutPostRedisplay();		// ???
}

void KeyboardFunc::KeyboardUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		mCamera[0].setMoveState('w', false);
		break;
	case 'a':
		mCamera[0].setMoveState('a', false);
		break;
	case 's':
		mCamera[0].setMoveState('s', false);
		break;
	case 'd':
		mCamera[0].setMoveState('d', false);
		break;
	}
	glutPostRedisplay();		// ???
}