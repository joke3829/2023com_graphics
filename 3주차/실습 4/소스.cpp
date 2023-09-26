#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<random>

struct Rect {
	bool up, left;
	bool zig_up = true;
	bool ver;
	bool bigger;
	int ver_count = 0;
	int zig_count = 0;
	float initial_position[4];
	float coor[4];
	float color[3];
};
Rect rect[5];

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> uid(0.0, 1.0);
std::uniform_int_distribution ud(0, 1);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char, int, int);
void Func_a(int);
void Func_i(int);
void Func_c(int);
void Func_o(int);
void Mouse(int, int, int, int);

float x_conversion(int);	// 마우스 x좌표를 gl좌표로 변경
float y_conversion(int);	// 마우스 y좌표를 gl좌표로 변경

int width, height;
int square;
bool push_a, push_i, push_c, push_o;

void main(int argc, char** argv)
{
	width = height = 800;
	square = 0;
	push_a = push_c = push_i = push_o = false;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width,height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 4");					// 윈도우 생성(윈도우 이름)

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
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < square; ++i) {
		glColor3f(rect[i].color[0], rect[i].color[1], rect[i].color[2]);
		glRectf(rect[i].coor[0], rect[i].coor[1], rect[i].coor[2], rect[i].coor[3]);
	}
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);;
}

GLvoid Keyboard(unsigned char key, int x , int y)
{
	switch (key) {
	case 'a':
		if (push_a)
			push_a = false;
		else {
			glutTimerFunc(100, Func_a, 1);
			push_a = true;
		}
		break;
	case 'i':
		if (push_i)
			push_i = false;
		else {
			glutTimerFunc(100, Func_i, 2);
			push_i = true;
		}
		break;
	case 'c':
		if (push_c)
			push_c = false;
		else {
			for (int i = 0; i < square; ++i) {
				rect[i].ver = ud(dre);
				rect[i].ver_count = 0;
				rect[i].bigger = true;
			}
			glutTimerFunc(100, Func_c, 3);
			push_c = true;
		}
		break;
	case 'o':
		if (push_o)
			push_o = false;
		else {
			glutTimerFunc(100, Func_o, 4);
			push_o = true;
		}
		break;
	case 's':
		push_a = push_c = push_i = push_o = false;
		break;
	case 'm':
		for (int i = 0; i < square; ++i) {
			for (int j = 0; j < 4; ++j) {
				rect[i].coor[j] = rect[i].initial_position[j];
			}
		}
		break;
	case 'r':
		square = 0;
		break;
	case 'q':
		glutDestroyWindow(1);
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	float coor_x = x_conversion(x);
	float coor_y = y_conversion(y);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::cout << "x: " << coor_x << std::endl;
		std::cout << "y: " << coor_y << std::endl;
		if (square != 5) {
			rect[square].up = rect[square].left = true;
			rect[square].coor[0] = coor_x - 0.1;
			rect[square].coor[1] = coor_y - 0.1;
			rect[square].coor[2] = coor_x + 0.1;
			rect[square].coor[3] = coor_y + 0.1;
			for (int i = 0; i < 3; ++i) {
				rect[square].color[i] = uid(dre);
			}
			for (int i = 0; i < 4; ++i) {
				rect[square].initial_position[i] =
					rect[square].coor[i];
			}
			square++;
		}
	}
	glutPostRedisplay();

}

float x_conversion(int x)
{
	return (static_cast<float>(x) - (width / 2)) / (width / 2);
}

float y_conversion(int y)
{
	return ((static_cast<float>(y) * -1 ) + (height / 2)) / (height / 2);
}

void Func_a(int value)
{
	for (int i = 0; i < square; ++i) {
		if (rect[i].up) {
			rect[i].coor[1] += 0.05;
			rect[i].coor[3] += 0.05;
			if (rect[i].coor[3] >= 1)
				rect[i].up = false;
		}
		else {
			rect[i].coor[1] -= 0.05;
			rect[i].coor[3] -= 0.05;
			if (rect[i].coor[1] <= -1)
				rect[i].up = true;
		}
		if (rect[i].left) {
			rect[i].coor[0] += 0.05;
			rect[i].coor[2] += 0.05;
			if (rect[i].coor[2] >= 1)
				rect[i].left = false;
		}
		else {
			rect[i].coor[0] -= 0.05;
			rect[i].coor[2] -= 0.05;
			if (rect[i].coor[0] <= -1)
				rect[i].left = true;
		}
	}
	glutPostRedisplay();
	if (push_a)
		glutTimerFunc(100, Func_a, 1);
}

void Func_i(int value)
{
	for (int i = 0; i < square; ++i) {
		if (rect[i].zig_up) {
			rect[i].coor[1] += 0.05;
			rect[i].coor[3] += 0.05;
			rect[i].zig_count++;
			if (rect[i].zig_count >= 5) {
				rect[i].zig_count = 0;
				rect[i].zig_up = false;
			}
		}
		else {
			rect[i].coor[1] -= 0.05;
			rect[i].coor[3] -= 0.05;
			rect[i].zig_count++;
			if (rect[i].zig_count >= 5) {
				rect[i].zig_count = 0;
				rect[i].zig_up = true;
			}
		}
		rect[i].coor[0] += 0.05;
		rect[i].coor[2] += 0.05;
		if (rect[i].coor[2] >= 1) {
			rect[i].coor[0] = -1;
			rect[i].coor[2] = -0.8;
		}
	}
	glutPostRedisplay();
	if (push_i)
		glutTimerFunc(100, Func_i, 2);
}

void Func_c(int value)
{
	for (int i = 0; i < square; ++i) {
		if (rect[i].ver) {
			if (rect[i].bigger) {
				rect[i].coor[1] -= 0.05;
				rect[i].ver_count++;
				if (rect[i].ver_count >= 5) {
					rect[i].ver_count = 0;
					rect[i].bigger = false;
				}
			}
			else {
				rect[i].coor[1] += 0.05;
				rect[i].ver_count++;
				if (rect[i].ver_count >= 5) {
					rect[i].ver_count = 0;
					rect[i].bigger = true;
				}
			}
		}
		else {
			if (rect[i].bigger) {
				rect[i].coor[2] += 0.05;
				rect[i].ver_count++;
				if (rect[i].ver_count >= 5) {
					rect[i].ver_count = 0;
					rect[i].bigger = false;
				}
			}
			else {
				rect[i].coor[2] -= 0.05;
				rect[i].ver_count++;
				if (rect[i].ver_count >= 5) {
					rect[i].ver_count = 0;
					rect[i].bigger = true;
				}
			}
		}
	}
	glutPostRedisplay();
	if (push_c)
		glutTimerFunc(100, Func_c, 3);
}

void Func_o(int value)
{
	for (int i = 0; i < square; ++i) {
		for (int j = 0; j < 3; ++j) {
			rect[i].color[j] = uid(dre);
		}
	}
	glutPostRedisplay();
	if (push_o)
		glutTimerFunc(100, Func_o, 4);
}