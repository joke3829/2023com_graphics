
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


// 상태가 바뀌면 그 때에 따라 새로운 자원을 받아와라
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

// 자원을 사용했으면 반납해라
void MainApp::DestroyMainApp()
{
	delete[] camera;
	delete proj;
	delete mesh_list;
	delete mKey;
	delete mMouse;
}