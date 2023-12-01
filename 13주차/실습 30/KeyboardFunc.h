//==================================================================
// KeyboardFunc.h
// 키보드 입력에 관여
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