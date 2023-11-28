
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
	std::cout << "행을 입력: ";
	std::cin >> row;

	std::cout << "열을 입력: ";
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


// 상태가 바뀌면 그 때에 따라 새로운 자원을 받아와라
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

// 자원을 사용했으면 반납해라
void MainApp::DestroyMainApp()
{

}