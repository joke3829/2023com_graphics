//==================================================================
// KeyboardFunc.h
// Ű���� �Է¿� ����
//=================================================================
#pragma once
#include "stdafx.h"

class CameraObj;
class KeyboardFunc {
public:
	KeyboardFunc(CameraObj*);

	void Keyboard(unsigned char, int, int);
	void KeyboardUp(unsigned char, int, int);

protected:
private:
	CameraObj* mCamera{ nullptr };
};