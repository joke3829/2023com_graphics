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

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int);
void Mouse(int, int, int, int);
void Motion(int, int);

int width, height, num_shape;
GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

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
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 12");					// ������ ����(������ �̸�)

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	shaderProgramID = make_shaderProgram();			// ���̴� ���α׷� �����
	for (Shape& a : shape)
		a.Gen();
	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutTimerFunc(50, TimerFunction, 0);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(shaderProgramID);

	for (Shape& a : shape)
		a.Draw();

	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)						// �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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