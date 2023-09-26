#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<ctime>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void Motion(int, int);

struct square {
	float x1, x2, y1, y2;
	float red, green, blue;
};
square rect[5];

int square_num;
int w_grab;
int oldx, oldy;

void main(int argc, char** argv)
{
	w_grab = 10;
	square_num = 1;
	rect[0].x1 = rect[0].y1 = -0.1;
	rect[0].x2 = rect[0].y2 = 0.1;
	rect[0].red = 1;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(800, 800);					// 윈도우의 크기 지정
	glutCreateWindow("실습 3");					// 윈도우 생성(윈도우 이름)

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
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < square_num; ++i) {
		glColor3f(rect[i].red, rect[i].green, rect[i].blue);
		glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
	}
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);;
}

void Keyboard(unsigned char key, int x, int y)
{
	float placex, placey;
	srand(time(NULL));
	switch (key) {
	case 'a':
		if (square_num < 5) {
			placex = rand() % 600 + 100;
			placey = rand() % 600 + 100;
			rect[square_num].x1 = (placex - 400) / 400 - 0.1;
			rect[square_num].x2 = (placex - 400) / 400 + 0.1;
			rect[square_num].y1 = (placey * -1 + 400) / 400 - 0.1;
			rect[square_num].y2 = (placey * -1 + 400) / 400 + 0.1;
			rect[square_num].red = (float)(rand() % 11) / 10;
			rect[square_num].green = (float)(rand() % 11) / 10;
			rect[square_num].blue = (float)(rand() % 11) / 10;
			square_num++;
		} 
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	float mx, my;
	mx = (float)(x - 400) / 400;
	my = (float)(y * -1 + 400) / 400;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = square_num - 1; i >= 0; --i) {
			if (rect[i].x1 <= mx && rect[i].x2 >= mx &&
				rect[i].y1 <= my && rect[i].y2 >= my) {
				oldx = x; oldy = y;
				w_grab = i;
				break;
			}
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		w_grab = 10;
	}
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	float b_x, b_y, a_x, a_y;
	b_x = (float)(oldx - 400) / 400;
	a_x = (float)(x - 400) / 400;
	a_y = (float)(y * -1 + 400) / 400;
	b_y = (float)(oldy * -1 + 400) / 400;
	
	if (w_grab >= 0 && w_grab <= 4) {
		rect[w_grab].x1 += (a_x - b_x);
		rect[w_grab].x2 += (a_x - b_x);
		rect[w_grab].y1 += (a_y - b_y);
		rect[w_grab].y2 += (a_y - b_y);
	}
	oldx = x;
	oldy = y;
	glutPostRedisplay();
}