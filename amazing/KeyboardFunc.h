//==================================================================
// KeyboardFunc.h
// Ű���� �Է¿� ����
//=================================================================
#pragma once
#include "stdafx.h"

class CameraObj;
class MeshList;
class KeyboardFunc {
public:
	KeyboardFunc(CameraObj*, MeshList*);

	void Keyboard(unsigned char, int, int);
	void KeyboardUp(unsigned char, int, int);

protected:
private:
	CameraObj* mCamera{ nullptr };
	MeshList* m_list{ nullptr };
};