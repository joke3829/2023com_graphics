//==========================================================
// MainApp.h
// ��� ������ ���� �� �Ѱ��Ѵ�
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

	void setRC();	// �� �� ����

	bool Render();
protected:
private:
	int row, col; // �� ��
	CameraObj* camera;
	ProjObj* proj;

	Mesh* mesh_array;

};