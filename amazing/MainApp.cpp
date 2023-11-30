
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
	mOrt = new OrtObj;
	mBottom = new Mesh;
	mBottom->F_Initalize();
	mesh_list = new MeshList;

	mLight = new LightObj;

	mKey = new KeyboardFunc(camera, mesh_list, mLight);
	mMouse = new MouseFunc(camera);

	camera[1].setCameraAngle(glm::vec2(90, -89.9999999999));
	camera[1].setCameraEYE(glm::vec3(12.5, 30, 12.5));

	return true;
}


// 상태가 바뀌면 그 때에 따라 새로운 자원을 받아와라
bool MainApp::Update_MainApp()
{
	camera[0].camera_move();
	mesh_list->mesh_ani();
	return true;
}

bool MainApp::Render()
{
	glViewport(0, 0, 1280, 720);
	proj->OutToShader();
	camera[0].OutToShader();
	mBottom->F_Render();
	mesh_list->Render();

	glViewport(1024, 576, 256, 144);
	mOrt->OutToShader();
	camera[1].OutToShader();

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