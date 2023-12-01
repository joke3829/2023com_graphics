
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


// 상태가 바뀌면 그 때에 따라 새로운 자원을 받아와라
bool MainApp::Update_MainApp()
{
	return true;
}

bool MainApp::Render()
{
	scene->Render();
	return true;
}

// 자원을 사용했으면 반납해라
void MainApp::DestroyMainApp()
{
	delete[] camera;
	delete proj;
	delete scene;
	delete mKey;
}