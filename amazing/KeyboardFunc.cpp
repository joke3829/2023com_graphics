
#include "KeyboardFunc.h"
#include "CameraObj.h"
#include "MeshList.h"
#include "LightObj.h"


KeyboardFunc::KeyboardFunc(CameraObj* t_camera, MeshList* t_list, LightObj* t_light)
	: mCamera(t_camera), m_list(t_list), mLight(t_light)
{
}

void KeyboardFunc::Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
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
		if(Mesh::frame_late > 18)
			Mesh::frame_late -= 1;
		break;
	case '-':
		if(Mesh::frame_late < 100)
			Mesh::frame_late += 1;
		break;
	case 't':
		mLight->lightButton();
		break;
	case '7':
		mLight->change_color(7);
		break;
	case '8':
		mLight->change_color(8);
		break;
	case '9':
		mLight->change_color(9);
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