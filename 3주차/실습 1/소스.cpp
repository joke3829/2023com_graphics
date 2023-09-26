#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<ctime>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);
float red, green, blue;
bool onTimer;

void main(int argc, char** argv)
{
	onTimer = false;
	red = green = blue = 0;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(250, 250);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 1");					// ������ ����(������ �̸�)

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)						// �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);;
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c':
		red = 0;
		green = 255;
		blue = 255;
		break;
	case 'm':
		red = 255;
		green = 0;
		blue = 255;
		break;
	case 'y':
		red = 255;
		green = 255;
		blue = 0;
		break;
	case 'a':
		srand(time(NULL));
		red = (float)(rand()%11)/10;
		green = (float)(rand() % 11)/10;
		blue = (float)(rand() % 11)/10;
		break;
	case 'w':
		red = green = blue = 255;
		break;
	case 'k':
		red = green = blue = 0;
		break;
	case 't':
		glutTimerFunc(1000, TimerFunction, 1);
		onTimer = true;
		break;
	case 's':
		onTimer = false;
		break;
	case 'q':
		glutDestroyWindow(1);
		break;
	}
	glutPostRedisplay();
}

void TimerFunction(int value) 
{
	srand(time(NULL));
	red = (float)(rand() % 11) / 10;
	green = (float)(rand() % 11) / 10;
	blue = (float)(rand() % 11) / 10;
	glutPostRedisplay();
	if(onTimer)
		glutTimerFunc(1000, TimerFunction, 1);
}