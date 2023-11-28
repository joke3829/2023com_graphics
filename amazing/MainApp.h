//==========================================================
// MainApp.h
// 모든 과정을 정리 및 총괄한다
//==========================================================

#include "stdafx.h"

class CameraObj;
class ProjObj;
class Mesh;

class MainApp {
public:
	~MainApp();

	bool Initialize();				
	bool Update_MainApp();
	void DestroyMainApp();

	void setRC();	// 행 열 지정

	bool Render();
protected:
private:
	int row, col; // 행 열
	CameraObj* camera;
	ProjObj* proj;

	Mesh* mesh_array;

};