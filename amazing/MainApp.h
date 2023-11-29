//==========================================================
// MainApp.h
// 모든 과정을 정리 및 총괄한다
//==========================================================

#include "stdafx.h"
#include "KeyboardFunc.h"
#include "MouseFunc.h"

class CameraObj;
class ProjObj;
class Mesh;
class MeshList;


class MainApp {
public:
	~MainApp();

	bool Initialize();				
	bool Update_MainApp();
	void DestroyMainApp();

	bool Render();
	KeyboardFunc* mKey;
	MouseFunc* mMouse;
protected:
private:
	CameraObj* camera;
	ProjObj* proj;

	Mesh* mBottom;
	MeshList* mesh_list;
};