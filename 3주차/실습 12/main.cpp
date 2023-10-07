#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<random>
#include "Filetobuf.h"
#include "Mouse.h"
#include "shape.h"

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> urd_coor(-0.8, 0.8);
std::uniform_real_distribution<float> urd_color(0.0, 1.0);

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int);
void Mouse(int, int, int, int);
void Motion(int, int);

int width, height, num_shape;
GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

Shape shape[15]{ {1, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{1, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{1, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{2, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{2, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{2, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{3, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{3, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{3, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{4, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{4, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{4, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{5, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{5, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)},
	{5, urd_coor(dre), urd_coor(dre), urd_color(dre), urd_color(dre), urd_color(dre)} };

void main(int argc, char** argv)
{
	num_shape = -1;
	width = height = 800;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 12");					// 윈도우 생성(윈도우 이름)

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	shaderProgramID = make_shaderProgram();			// 셰이더 프로그램 만들기
	for (Shape& a : shape)
		a.Gen();
	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutTimerFunc(50, TimerFunction, 0);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(shaderProgramID);

	for (Shape& a : shape)
		a.Draw();

	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
{
	w = width; h = height;
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

void TimerFunction(int value)
{
	for (Shape& a : shape)
		a.move();
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 0);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 14; i > -1; --i) {
			if (shape[i].check_grab(x_conversion(x, width), y_conversion(y, height))) {
				num_shape = i;
				break;
			}
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		for (int i = 14; i > -1; --i) {
			if (i == num_shape)
				continue;
			if (shape[i].check_grab(x_conversion(x, width), y_conversion(y, height))) {
				shape[i].merge_shape(shape[num_shape]);
			}
		}
		num_shape = -1;
	}
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	if (num_shape > -1 && num_shape < 15) {
		shape[num_shape].move_mouse(x_conversion(x, width), y_conversion(y, height));
		glutPostRedisplay();
	}
}