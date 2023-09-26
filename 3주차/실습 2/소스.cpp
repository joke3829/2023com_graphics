#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
float red, green, blue;

void Mouse(int, int, int, int);

struct square {
	float x1, y1, x2, y2;
	float red, green, blue;
};

square rect1 = { -1, 0, 0, 1, 1, 0, 0 };
square rect2 = { 0, 0, 1, 1, 0, 1, 0 };
square rect3 = { -1, -1, 0, 0, 0, 0, 1 };
square rect4 = { 0, -1, 1, 0, 1, 1, 0 };

void main(int argc, char** argv)
{
	int red = green = blue = 0;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);				// 윈도우의 위치 지정
	glutInitWindowSize(800, 800);					// 윈도우의 크기 지정
	glutCreateWindow("실습 2");					// 윈도우 생성(윈도우 이름)

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
	glutMouseFunc(Mouse);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(rect1.red, rect1.green, rect1.blue);
	glRectf(rect1.x1, rect1.y1, rect1.x2, rect1.y2);

	glColor3f(rect2.red, rect2.green, rect2.blue);
	glRectf(rect2.x1, rect2.y1, rect2.x2, rect2.y2);

	glColor3f(rect3.red, rect3.green, rect3.blue);
	glRectf(rect3.x1, rect3.y1, rect3.x2, rect3.y2);

	glColor3f(rect4.red, rect4.green, rect4.blue);
	glRectf(rect4.x1, rect4.y1, rect4.x2, rect4.y2);
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);;
}

void Mouse(int button, int state, int x, int y)
{
	float mx, my;
	mx = ((float)x - 400) / 400;
	my = ((float)y * -1 + 400) / 400;
	srand(time(NULL));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		std::cout << "x = " << x << " y = " << y << std::endl;
	if (mx >= -1 && mx < 0 && my >= 0 && my < 1) {	//1번 섹터
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (mx >= rect1.x1 && mx <= rect1.x2 &&
				my >= rect1.y1 && my <= rect1.y2) {
				rect1.red = (float)(rand() % 11) / 10;
				rect1.green = (float)(rand() % 11) / 10;
				rect1.blue = (float)(rand() % 11) / 10;
			}
			else {
				red = (float)(rand() % 11) / 10;
				green = (float)(rand() % 11) / 10;
				blue = (float)(rand() % 11) / 10;
			}
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			if (mx >= rect1.x1 && mx <= rect1.x2 &&
				my >= rect1.y1 && my <= rect1.y2) {
				rect1.x1 += 0.1; rect1.x2 -= 0.1;
				rect1.y1 += 0.1; rect1.y2 -= 0.1;
			}
			else {
				rect1.x1 -= 0.1; rect1.x2 += 0.1;
				rect1.y1 -= 0.1; rect1.y2 += 0.1;
			}
		}
	}
	else if (mx >= 0 && mx < 1 && my >= 0 && my < 1) {	// 2번 섹터
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (mx >= rect2.x1 && mx <= rect2.x2 &&
				my >= rect2.y1 && my <= rect2.y2) {
				rect2.red = (float)(rand() % 11) / 10;
				rect2.green = (float)(rand() % 11) / 10;
				rect2.blue = (float)(rand() % 11) / 10;
			}
			else {
				red = (float)(rand() % 11) / 10;
				green = (float)(rand() % 11) / 10;
				blue = (float)(rand() % 11) / 10;
			}

		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			if (mx >= rect2.x1 && mx <= rect2.x2 &&
				my >= rect2.y1 && my <= rect2.y2) {
				rect2.x1 += 0.1; rect2.x2 -= 0.1;
				rect2.y1 += 0.1; rect2.y2 -= 0.1;
			}
			else {
				rect2.x1 -= 0.1; rect2.x2 += 0.1;
				rect2.y1 -= 0.1; rect2.y2 += 0.1;
			}
		}
	}
	else if (mx >= -1 && mx < 0 && my >= -1 && my < 0) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (mx >= rect3.x1 && mx <= rect3.x2 &&
				my >= rect3.y1 && my <= rect3.y2) {
				rect3.red = (float)(rand() % 11) / 10;
				rect3.green = (float)(rand() % 11) / 10;
				rect3.blue = (float)(rand() % 11) / 10;
			}
			else {
				red = (float)(rand() % 11) / 10;
				green = (float)(rand() % 11) / 10;
				blue = (float)(rand() % 11) / 10;
			}
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			if (mx >= rect3.x1 && mx <= rect3.x2 &&
				my >= rect3.y1 && my <= rect3.y2) {
				rect3.x1 += 0.1; rect3.x2 -= 0.1;
				rect3.y1 += 0.1; rect3.y2 -= 0.1;
			}
			else {
				rect3.x1 -= 0.1; rect3.x2 += 0.1;
				rect3.y1 -= 0.1; rect3.y2 += 0.1;
			}
		}
	}
	else if (mx >= 0 && mx < 1 && my >= -1 && my < 0) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (mx >= rect4.x1 && mx <= rect4.x2 &&
				my >= rect4.y1 && my <= rect4.y2) {
				rect4.red = (float)(rand() % 11) / 10;
				rect4.green = (float)(rand() % 11) / 10;
				rect4.blue = (float)(rand() % 11) / 10;
			}
			else {
				red = (float)(rand() % 11) / 10;
				green = (float)(rand() % 11) / 10;
				blue = (float)(rand() % 11) / 10;
			}
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			if (mx >= rect4.x1 && mx <= rect4.x2 &&
				my >= rect4.y1 && my <= rect4.y2) {
				rect4.x1 += 0.1; rect4.x2 -= 0.1;
				rect4.y1 += 0.1; rect4.y2 -= 0.1;
			}
			else {
				rect4.x1 -= 0.1; rect4.x2 += 0.1;
				rect4.y1 -= 0.1; rect4.y2 += 0.1;
			}
		}
	}
	glutPostRedisplay();
}