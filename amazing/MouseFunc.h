//==================================================================
// MouseFunc.h
// ���콺�� ����
//=================================================================
#pragma once
#include "stdafx.h"

class CameraObj;
class MouseFunc {
public:
	MouseFunc(CameraObj*);

	void Mouse(int,int, int, int);
	void MotionPassive( int, int);

protected:
private:
	CameraObj* mCamera;
};