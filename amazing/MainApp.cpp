
#include "MainApp.h"
#include "main_define.h"

MainApp::~MainApp()
{
	DestroyMainApp();
}

bool MainApp::Initialize()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	camera = new CameraObj[2];
	proj = new ProjObj;
	mBottom = new Mesh;
	mBottom->F_Initalize();
	mesh_list = new MeshList;

	mKey = new KeyboardFunc(camera, mesh_list);
	mMouse = new MouseFunc(camera);

	return true;
}


// ���°� �ٲ�� �� ���� ���� ���ο� �ڿ��� �޾ƿͶ�
bool MainApp::Update_MainApp()
{
	camera->camera_move();
	mesh_list->mesh_ani();
	return true;
}

bool MainApp::Render()
{
	mBottom->F_Render();
	mesh_list->Render();
	return true;
}

// �ڿ��� ��������� �ݳ��ض�
void MainApp::DestroyMainApp()
{
	delete[] camera;
	delete proj;
	delete mesh_list;
	delete mKey;
	delete mMouse;
}