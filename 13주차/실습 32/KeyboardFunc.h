//==================================================================
// KeyboardFunc.h
// Ű���� �Է¿� ����
//=================================================================
#pragma once
#include "stdafx.h"
#include "Scene.h"

class CameraObj;

class KeyboardFunc {
public:
	KeyboardFunc(CameraObj*, Scene_1*);

	void Keyboard(unsigned char, int, int);
	void KeyboardUp(unsigned char, int, int);

protected:
private:
	CameraObj* mCamera{ nullptr };
	Scene_1* scene{ nullptr };
};