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
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(250, 250);					// 윈도우의 크기 지정
	glutCreateWindow("실습 1");					// 윈도우 생성(윈도우 이름)

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
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