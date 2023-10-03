#define _USE_MATH_DEFINES
#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<random>
#include<cmath>
#include "Filetobuf.h"
#include "Mouse.h"
#include "spiral.h"

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> urd_color(0.0, 1.0);
std::uniform_real_distribution<float> urd_coor(-0.82, 0.82);

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
int start, end;
bool show_line, activate_timer;
GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

float red, green, blue;
int show_num;
SPIRAL spiral[5];

void main(int argc, char** argv)
{
	show_num = 1;
	show_line = false;
	red = green = blue = 0.0;
	width = height = 800;
	start = end = 0;
	activate_timer = false;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 10");					// 윈도우 생성(윈도우 이름)

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	for (int i = 0; i < 5; ++i)
		spiral[i].Gen();
	shaderProgramID = make_shaderProgram();			// 셰이더 프로그램 만들기

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	for (int i = 0; i < show_num; ++i) {
		spiral[i].InitBuffer();
		spiral[i].Draw(show_line, start, end);
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

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
		show_line = false;
		break;
	case 'l':
		show_line = true;
		break;
	case '1':
		end = 0;
		red = urd_color(dre);
		green = urd_color(dre);
		blue = urd_color(dre);
		show_num = 1;
		for (int i = 0; i < show_num; ++i) {
			spiral[i].decide_point(urd_coor(dre), urd_coor(dre));
		}
		if (!activate_timer) { 
			activate_timer = true;
			glutTimerFunc(80, TimerFunction, 0);
		}
		break;
	case '2':
		end = 0;
		red = urd_color(dre);
		green = urd_color(dre);
		blue = urd_color(dre);
		show_num = 2;
		for (int i = 0; i < show_num; ++i) {
			spiral[i].decide_point(urd_coor(dre), urd_coor(dre));
		}
		if (!activate_timer) {
			activate_timer = true;
			glutTimerFunc(80, TimerFunction, 0);
		}
		break;
	case '3':
		end = 0;
		red = urd_color(dre);
		green = urd_color(dre);
		blue = urd_color(dre);
		show_num = 3;
		for (int i = 0; i < show_num; ++i) {
			spiral[i].decide_point(urd_coor(dre), urd_coor(dre));
		}
		if (!activate_timer) {
			activate_timer = true;
			glutTimerFunc(80, TimerFunction, 0);
		}
		break;
	case '4':
		end = 0;
		red = urd_color(dre);
		green = urd_color(dre);
		blue = urd_color(dre);
		show_num = 4;
		for (int i = 0; i < show_num; ++i) {
			spiral[i].decide_point(urd_coor(dre), urd_coor(dre));
		}
		if (!activate_timer) {
			activate_timer = true;
			glutTimerFunc(80, TimerFunction, 0);
		}
		break;
	case '5':
		end = 0;
		red = urd_color(dre);
		green = urd_color(dre);
		blue = urd_color(dre);
		show_num = 5;
		for (int i = 0; i < show_num; ++i) {
			spiral[i].decide_point(urd_coor(dre), urd_coor(dre));
		}
		if (!activate_timer) {
			activate_timer = true;
			glutTimerFunc(80, TimerFunction, 0);
		}
		break;
	}
	glutPostRedisplay();
} 

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		show_num = 1;
		red = urd_color(dre);
		green = urd_color(dre);
		blue = urd_color(dre);
		end = 0;
		spiral[0].decide_point(x_conversion(x, width), y_conversion(y, height));
		if (!activate_timer) {
			activate_timer = true;
			glutTimerFunc(80, TimerFunction, 0);
		}
		glutPostRedisplay();
	}
}

void TimerFunction(int value)
{
	if (end < 76) {
		end++;
		glutTimerFunc(80, TimerFunction, 0);
	}
	else if(end >= 76)
		activate_timer = false;
	glutPostRedisplay();
}