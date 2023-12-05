//==========================================================
// MainApp.h
// ��� ������ ���� �� �Ѱ��Ѵ�
//==========================================================

#include "stdafx.h"
#include "KeyboardFunc.h"

class CameraObj;
class ProjObj;
class Mesh;


class MainApp {
public:
	~MainApp();

	bool Initialize();				
	bool Update_MainApp();
	void DestroyMainApp();

	bool Render();
	KeyboardFunc* mKey;
protected:
private:
	CameraObj* camera;
	ProjObj* proj;

	Scene_1* scene;
};