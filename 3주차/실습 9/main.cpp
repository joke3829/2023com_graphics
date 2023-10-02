#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<random>
#include "Filetobuf.h"
#include "Mouse.h"
#include"Shape.h"

std::random_device rd;
std::mt19937 dre(rd());
std::uniform_real_distribution<float> spd(0.01, 0.05);
std::uniform_real_distribution<float> urd(0.0, 1.0);
std::uniform_real_distribution<float> rdsize(0.05, 0.3);

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction_1(int);
void TimerFunction_2(int);
void TimerFunction_3(int);
void TimerFunction_4(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

bool push_1, push_2, push_3, push_4;
bool moving;

Shape shape[4] = { {-0.6, 0.3, -0.4, 0.3, -0.5, 0.6, urd(dre), urd(dre), urd(dre), spd(dre)},
	{0.4, 0.3, 0.6, 0.3, 0.5, 0.6, urd(dre), urd(dre), urd(dre), spd(dre)},
	{-0.6, -0.7, -0.4, -0.7, -0.5, -0.4, urd(dre), urd(dre), urd(dre), spd(dre)},
	{0.4, -0.7, 0.6, -0.7, 0.5, -0.4, urd(dre), urd(dre), urd(dre), spd(dre)}};

void main(int argc, char** argv)
{
	moving = false;
	push_1 = push_2 = push_3 = push_4 = false;
	width = height = 800;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 8");					// 윈도우 생성(윈도우 이름)

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	for (int i = 0; i < 4; ++i) {
		shape[i].Gen();
	}
	shaderProgramID = make_shaderProgram();			// 셰이더 프로그램 만들기

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgramID);
	for (int i = 0; i < 4; ++i) {
		shape[i].InitBuffer();
		shape[i].Draw();
	}

	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void make_vertexShaders()
{
	GLchar* vertexSource;
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	fragmentSource = filetobuf("fragment.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
}

GLuint make_shaderProgram()
{
	make_vertexShaders();							// vertexShader 만들기
	make_fragmentShaders();							// 프래그먼트 셰이더 만들기
	GLuint shaderID = glCreateProgram();

	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);

	glLinkProgram(shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderID);
	return shaderID;
}

void Mouse(int button, int state, int x, int y)
{
	if (!moving) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (x_conversion(x, width) < 0 && y_conversion(y, height) > 0) {
				shape[0].change_coor(x_conversion(x, width), y_conversion(y, height),
					rdsize(dre), rdsize(dre));
			}
			else if (x_conversion(x, width) > 0 && y_conversion(y, height) > 0) {
				shape[1].change_coor(x_conversion(x, width), y_conversion(y, height),
					rdsize(dre), rdsize(dre));
			}
			else if (x_conversion(x, width) < 0 && y_conversion(y, height) < 0) {
				shape[2].change_coor(x_conversion(x, width), y_conversion(y, height),
					rdsize(dre), rdsize(dre));
			}
			else if (x_conversion(x, width) > 0 && y_conversion(y, height) < 0) {
				shape[3].change_coor(x_conversion(x, width), y_conversion(y, height),
					rdsize(dre), rdsize(dre));
			}
		}
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		for (int i = 0; i < 4; ++i) {
			shape[i].change_line(false);
		}
		break;
	case 'b':
		for (int i = 0; i < 4; ++i) {
			shape[i].change_line(true);
		}
		break;
	case '1':
		if (push_1) {
			push_1 =  moving = false;
		}
		else {
			for (int i = 0; i < 4; ++i) {
				shape[i].set_bool();
			}
			glutTimerFunc(100, TimerFunction_1, 1);
			push_1 = moving = true;
		}
		push_2 = push_3 = push_4 = false;
		break;
	case '2':
		if (push_2) {
			push_2 = moving = false;
		}
		else {
			glutTimerFunc(100, TimerFunction_2, 2);
			push_2 = moving = true;
		}
		push_1 = push_3 = push_4 = false;
		break;
	case '3':
		if (push_3) {
			push_3 = moving =  false;
		}
		else {
			for (int i = 0; i < 4; ++i) {
				shape[i].change_coor(0.9, -0.85, 0, 0);
				shape[i].set_count();
			}
			glutTimerFunc(100, TimerFunction_3, 3);
			push_3 = moving = true;
		}
		push_1 = push_2 = push_4 = false;
		break;
	case '4':
		if (push_4) {
			push_4 = moving = false;
		}
		else {
			for (int i = 0; i < 4; ++i) {
				shape[i].set_rad(0);
				shape[i].change_coor(0, 0, 0, 0);
			}
			glutTimerFunc(100, TimerFunction_4, 4);
			push_4 = moving =  true;
		}
		push_1 = push_2 = push_3 = false;
		break;
	}
	glutPostRedisplay();
}

void TimerFunction_1(int value) 
{
	for (int i = 0; i < 4; ++i) {
		shape[i].move_1();
	}
	glutPostRedisplay();
	if (push_1)
		glutTimerFunc(100, TimerFunction_1, 1);
}

void TimerFunction_2(int value)
{
	for (int i = 0; i < 4; ++i) {
		shape[i].move_2();
	}
	glutPostRedisplay();
	if (push_2)
		glutTimerFunc(100, TimerFunction_2, 2);
}

void TimerFunction_3(int value)
{
	for (int i = 0; i < 4; ++i) {
		shape[i].move_3();
	}
	glutPostRedisplay();
	if (push_3)
		glutTimerFunc(100, TimerFunction_3, 3);
}

void TimerFunction_4(int value)
{
	for (int i = 0; i < 4; ++i) {
		shape[i].move_4();
	}
	glutPostRedisplay();
	if (push_4)
		glutTimerFunc(100, TimerFunction_4, 4);
}