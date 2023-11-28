#include "MouseFunc.h"
#include "CameraObj.h"

MouseFunc::MouseFunc(CameraObj* t_player)
	: mCamera(t_player)
{
}

void MouseFunc::Mouse(int button, int state, int x, int y)
{

	glutPostRedisplay();		// ???
}

void MouseFunc::MotionPassive(int x, int y)
{
	int Dx = x - 1280 / 2;
	int Dy = y - 720 / 2;
	float Dxf = Dx * (0.1);
	float Dyf = Dy * (0.1);

	mCamera->update_angle(Dxf, -Dyf);
	glutWarpPointer(1280 / 2, 720 / 2);
	glutPostRedisplay();		// ???
}