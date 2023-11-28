
#include "KeyboardFunc.h"
#include "CameraObj.h"


KeyboardFunc::KeyboardFunc(CameraObj* t_camera)
	:  mCamera(t_camera)
{
}

void KeyboardFunc::Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		mCamera->setMoveState('w', true);
		break;
	case 'a':
		mCamera->setMoveState('a', true);
		break;
	case 's':
		mCamera->setMoveState('s', true);
		break;
	case 'd':
		mCamera->setMoveState('d', true);
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	case 'r':

		break;
	}
	glutPostRedisplay();		// ???
}

void KeyboardFunc::KeyboardUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		mCamera->setMoveState('w', false);
		break;
	case 'a':
		mCamera->setMoveState('a', false);
		break;
	case 's':
		mCamera->setMoveState('s', false);
		break;
	case 'd':
		mCamera->setMoveState('d', false);
		break;
	}
	glutPostRedisplay();		// ???
}