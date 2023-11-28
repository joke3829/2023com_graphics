//==========================================================
// MainApp.h
// ��� ������ ���� �� �Ѱ��Ѵ�
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

	void setRC();	// �� �� ����
	void delete_RC();	// �޽� �迭 ����
	void RC_init();		// �޽� �迭 �ʱ�ȭ

	bool Render();
	KeyboardFunc* mKey;
	MouseFunc* mMouse;
protected:
private:
	int row, col; // �� ��
	CameraObj* camera;
	ProjObj* proj;


	Mesh** mesh_array;

};