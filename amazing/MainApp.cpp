
#include "MainApp.h"
#include "main_define.h"

MainApp::~MainApp()
{
	DestroyMainApp();
}

// �������� �̰� ����Ұ�
bool MainApp::Initialize()
{
	row = col = 0;
	return true;
}


// ���°� �ٲ�� �� ���� ���� ���ο� �ڿ��� �޾ƿͶ�
bool MainApp::Update_MainApp()
{
	return true;
}

bool MainApp::Render()
{
	return true;
}

// �ڿ��� ��������� �ݳ��ض�
void MainApp::DestroyMainApp()
{

}