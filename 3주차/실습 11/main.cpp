#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include "Filetobuf.h"
#include"triangle.h"
#include "square.h"
#include "pentagon.h"
#include"point.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

int width, height, w_display;
GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

TRIANGLE triangle;
SQUARE square;
PENTAGON pentagon;
PEN_POINT pen_point;

void main(int argc, char** argv)
{
	w_display = 5;
	width = height = 800;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 11");					// ������ ����(������ �̸�)

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew �ʱ�ȭ
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
	shaderProgramID = make_shaderProgram();			// ���̴� ���α׷� �����

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 0);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
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