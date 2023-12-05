
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
	scene = new Scene_1;

	mKey = new KeyboardFunc(camera, scene);

	return true;
}


// ���°� �ٲ�� �� ���� ���� ���ο� �ڿ��� �޾ƿͶ�
bool MainApp::Update_MainApp()
{
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