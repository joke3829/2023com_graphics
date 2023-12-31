#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include "Filetobuf.h"
#include"triangle.h"
#include "square.h"
#include "pentagon.h"
#include"point.h"

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

int width, height, w_display;
GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

TRIANGLE triangle;
SQUARE square;
PENTAGON pentagon;
PEN_POINT pen_point;

void main(int argc, char** argv)
{
	w_display = 5;
	width = height = 800;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 11");					// 윈도우 생성(윈도우 이름)

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	triangle.Gen();
	square.Gen();
	pentagon.Gen();
	pen_point.Gen();
	shaderProgramID = make_shaderProgram();			// 셰이더 프로그램 만들기

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 0);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);

	switch (w_display) {
	case 1:
		triangle.InitBuffer();
		triangle.Draw();
		break;
	case 2:
		square.InitBuffer();
		square.Draw();
		break;
	case 3:
		pentagon.InitBuffer();
		pentagon.Draw();
		break;
	case 4:
		pen_point.InitBuffer();
		pen_point.Draw();
		break;
	case 5:
		triangle.InitBuffer();
		triangle.Draw();
		square.InitBuffer();
		square.Draw();
		pentagon.InitBuffer();
		pentagon.Draw();
		pen_point.InitBuffer();
		pen_point.Draw();
		break;
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
	case 'l':
		w_display = 1;
		break;
	case 't':
		w_display = 2;
		break;
	case 'r':
		w_display = 3;
		break;
	case 'p':
		w_display = 4;
		break;
	case 'a':
		w_display = 5;
		break;
	}
	triangle.initial(w_display);
	square.initial(w_display);
	pentagon.initial(w_display);
	pen_point.initial(w_display);
	glutPostRedisplay();
}

void TimerFunction(int)
{
	triangle.transform(w_display);
	square.transform(w_display);
	pentagon.transform(w_display);
	pen_point.transform(w_display);
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 0);
}