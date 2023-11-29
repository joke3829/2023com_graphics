
#include "KeyboardFunc.h"
#include "CameraObj.h"
#include "MeshList.h"


KeyboardFunc::KeyboardFunc(CameraObj* t_camera, MeshList* t_list)
	: mCamera(t_camera), m_list(t_list)
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
		m_list->delete_RC();
		m_list->setRC();
		m_list->RC_init();
		break;
	case '1':
		m_list->setAS(1);
		break;
	case '2':
		m_list->setAS(2);
		break;
	case '3':
		m_list->setAS(3);
		break;
	case '+':
		Mesh::frame_late -= 1;
		break;
	case '-':
		Mesh::frame_late += 1;
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