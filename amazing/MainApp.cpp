
#include "MainApp.h"
#include "main_define.h"

MainApp::~MainApp()
{
	DestroyMainApp();
}

// 최종본엔 이걸 사용할것
bool MainApp::Initialize()
{
	row = col = 0;
	return true;
}


// 상태가 바뀌면 그 때에 따라 새로운 자원을 받아와라
bool MainApp::Update_MainApp()
{
	return true;
}

bool MainApp::Render()
{
	return true;
}

// 자원을 사용했으면 반납해라
void MainApp::DestroyMainApp()
{

}