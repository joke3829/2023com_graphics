//==================================================================
// KeyboardFunc.h
// Ű���� �Է¿� ����
//=================================================================
#pragma once
#include "stdafx.h"

class CameraObj;
class MeshList;
class LightObj;
class KeyboardFunc {
public:
	KeyboardFunc(CameraObj*, MeshList*, LightObj*);

	void Keyboard(unsigned char, int, int);
	void KeyboardUp(unsigned char, int, int);

protected:
private:
	CameraObj* mCamera{ nullptr };
	MeshList* m_list{ nullptr };
	LightObj* mLight{ nullptr };
};