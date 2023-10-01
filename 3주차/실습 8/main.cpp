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
std::uniform_real_distribution<float> urd(0.0, 1.0);
std::uniform_real_distribution<float> rdsize(0.05, 0.3);

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Shape shape[4] = { {-0.65, 0.25, -0.35, 0.25, -0.5, 0.75, urd(dre), urd(dre), urd(dre)},
	{0.35, 0.25, 0.65, 0.25, 0.5, 0.75, urd(dre), urd(dre), urd(dre)},
	{-0.65, -0.75, -0.35, -0.75, -0.5, -0.25, urd(dre), urd(dre), urd(dre)},
	{0.35, -0.75, 0.65, -0.75, 0.5, -0.25, urd(dre), urd(dre), urd(dre)} };

void main(int argc, char** argv)
{
	width = height = 800;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 8");					// ������ ����(������ �̸�)

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	for (int i = 0; i < 4; ++i) {
		shape[i].Gen();
	}
	shaderProgramID = make_shaderProgram();			// ���̴� ���α׷� �����

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgramID);
	for (int i = 0; i < 4; ++i) {
		shape[i].InitBuffer();
		shape[i].Draw();
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

void Mouse(int button, int state, int x, int y)
{
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
	}
	glutPostRedisplay();
}