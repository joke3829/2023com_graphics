//==================================================================
// MouseFunc.h
// 마우스에 관여
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