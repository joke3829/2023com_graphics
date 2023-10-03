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

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
int start, end;
bool show_line, activate_timer;
GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

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
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 10");					// ������ ����(������ �̸�)

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	for (int i = 0; i < 5; ++i)
		spiral[i].Gen();
	shaderProgramID = make_shaderProgram();			// ���̴� ���α׷� �����

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	for (int i = 0; i < show_num; ++i) {
		spiral[i].InitBuffer();
		spiral[i].Draw(show_line, start, end);
	}
	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)						// �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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
	make_vertexShaders();							// vertexShader �����
	make_fragmentShaders();							// �����׸�Ʈ ���̴� �����
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