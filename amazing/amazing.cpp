

#include "MainApp.h"
//#include "Mouse.h"
#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);



int width, height;			// ��Ⱦ ũ��
double frameTime;			// ��� �ð�


void Timer(int);			// Ÿ�̸� ���
std::unique_ptr<MainApp> mainApp(new MainApp);		// MainApp ����

void main(int argc, char** argv)
{
	width = 1280;
	height = 720;
	frameTime = 1000.0f / 60.0f;			// 1�ʿ� 60�� ���
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�¡ ������");					// ������ ����(������ �̸�)

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	std::cout << "==================���۹�==================" << '\n';
	std::cout << "1: �ִϸ��̼� 1\n2: �ִϸ��̼� 2\n3: �ִϸ��̼� 3" << '\n';
	std::cout << "t: ���� �ѱ�/����" << '\n';
	std::cout << "7, 8, 9: ����� ����/�ʷ�/�Ķ� ���� �ٲٱ�" << '\n';
	std::cout << "+, -: �ӵ� ����/����" << '\n';
	std::cout << "r: ũ�� ���Է�" << '\n';
	std::cout << "ESC: ���α׷� ����" << '\n';
	std::cout << "==========================================" << '\n';
	std::cout << "================ī�޶� ����===============" << '\n';
	std::cout << "w, a, s, d: ī�޶� ������" << '\n';
	std::cout << "���콺 ������: ī�޶� �ü� �̵�" << '\n';
	std::cout << "==========================================" << '\n';

	//============================================================
	if (not mainApp->Initialize()) {				// MainApp �ʱ�ȭ
		std::cout << "MainApp �ʱ�ȭ ����!" << std::endl;
		return;
	}
	//============================================================

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc([](unsigned char key, int x, int y) {
		mainApp->mKey->Keyboard(key, x, y);
	});
	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		mainApp->mKey->KeyboardUp(key, x, y);
	});
	glutMotionFunc([](int x, int y) {
		mainApp->mMouse->MotionPassive(x, y);
		});
	glutPassiveMotionFunc([](int x, int y) {
		mainApp->mMouse->MotionPassive(x, y);
		});
	glutTimerFunc(frameTime, Timer, 0);
	glutMainLoop();									// �̺�Ʈ ó�� ����

}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	if (not mainApp->Render())
		return;

	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)						// �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

void Timer(int value)
{
	mainApp->Update_MainApp();
	glutPostRedisplay();
	glutTimerFunc(frameTime, Timer, 0);
}