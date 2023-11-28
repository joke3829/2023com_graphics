
#include "MainApp.h"
#include "main_define.h"

MainApp::~MainApp()
{
	DestroyMainApp();
}

bool MainApp::Initialize()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	row = col = 0;
	camera = new CameraObj[2];
	proj = new ProjObj;

	mKey = new KeyboardFunc(camera);
	mMouse = new MouseFunc(camera);

	setRC();
	RC_init();

	return true;
}

void MainApp::setRC()
{
	std::cout << "���� �Է�: ";
	std::cin >> row;

	std::cout << "���� �Է�: ";
	std::cin >> col;

	mesh_array = new Mesh* [row];
	for (int i = 0; i < row; ++i) {
		mesh_array[i] = new Mesh[col];
	}
}

void MainApp::delete_RC()
{
	for (int i = 0; i < row; ++i) {
		delete[] mesh_array[i];
	}
	delete mesh_array;
}

void MainApp::RC_init()
{
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			mesh_array[i][j].Initialize("cube.obj");
			mesh_array[i][j].init_scale(0.1);
			mesh_array[i][j].init_position(i, 0.5, j);
		}
	}
}


// ���°� �ٲ�� �� ���� ���� ���ο� �ڿ��� �޾ƿͶ�
bool MainApp::Update_MainApp()
{
	camera->camera_move();
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			mesh_array[i][j].setSV();
		}
	}
	return true;
}

bool MainApp::Render()
{
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			mesh_array[i][j].Render();
		}
	}
	return true;
}

// �ڿ��� ��������� �ݳ��ض�
void MainApp::DestroyMainApp()
{

}