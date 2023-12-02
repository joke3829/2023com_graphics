
#include "MainApp.h"
#include "main_define.h"

MainApp::~MainApp()
{
	DestroyMainApp();
}

bool MainApp::Initialize()
{
	camera = new CameraObj;
	proj = new ProjObj;
	light = new LightObj;

	scene = new Scene_1;

	mKey = new KeyboardFunc(camera, scene, light);
	mMouse = new MouseFunc(camera);

	return true;
}


// ���°� �ٲ�� �� ���� ���� ���ο� �ڿ��� �޾ƿͶ�
bool MainApp::Update_MainApp()
{
	camera->camera_move();
	scene->s_ani();
	return true;
}

bool MainApp::Render()
{
	scene->Render();
	return true;
}

// �ڿ��� ��������� �ݳ��ض�
void MainApp::DestroyMainApp()
{
	delete[] camera;
	delete proj;
	delete scene;
	delete mKey;
}