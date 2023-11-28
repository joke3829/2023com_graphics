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


class MainApp {
public:
	~MainApp();

	bool Initialize();				
	bool Update_MainApp();
	void DestroyMainApp();

	void setRC();	// 행 열 지정
	void delete_RC();	// 메시 배열 삭제
	void RC_init();		// 메시 배열 초기화

	bool Render();
	KeyboardFunc* mKey;
	MouseFunc* mMouse;
protected:
private:
	int row, col; // 행 열
	CameraObj* camera;
	ProjObj* proj;


	Mesh** mesh_array;

};