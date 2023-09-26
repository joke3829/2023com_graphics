#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<random>

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> color_urd(0.0, 1.0);
std::uniform_real_distribution<float> coor_urd(-0.6, 0.6);
std::uniform_int_distribution method(0, 2);

struct Rect {			// 작은 사각형
	float color[3];		// 작은 사각형 색깔
	float coor[2] = { 0, 0 };		// 작은 사각형 좌표
	float size = 0.2;			// 작은 사각형 크기
	int move_way;		// 어디로 움직일지 방향(넘패드 기준)
	int rect_num;		// 몇번째 rect에 포함됐나
	bool flag = false;	// 클릭 됐나?
};
Rect rect[40];

struct BIGRECT {
	float x;
	float y;
	float size = 0.4;
	int move_method;	// 어떤 방법으로 퍼질거냐
	float color[3];
};
BIGRECT bigRect[5];

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void TimerFunc(int);

float x_conversion(int);			// 윈도우 x좌표를 gl죄표로 바꿔주는 함수
float y_conversion(int);			// 윈도우 y좌표를 gl좌표로 바꿔주는 함수

int width, height;
int total_rect = 0;

void main(int argc, char** argv)
{
	width = height = 800;
	// 큰 사각형 정보 넣어주기
	for (int i = 0; i < 5; ++i) {
		bigRect[i].move_method = method(dre);
		bigRect[i].x = coor_urd(dre);
		bigRect[i].y = coor_urd(dre);
		for (int j = 0; j < 3; ++j) {
			bigRect[i].color[j] = color_urd(dre);
		}
		switch (bigRect[i].move_method) {
		case 0:		// 상하좌우 네방향
			for (int j = total_rect; j < total_rect + 4; ++j) {
				rect[j].rect_num = i;
				switch (j - total_rect) {
				case 0:
					rect[j].move_way = 2;
					break;
				case 1:
					rect[j].move_way = 6;
					break;
				case 2:
					rect[j].move_way = 4;
					break;
				case 3:
					rect[j].move_way = 8;
					break;
				}
				rect[j].coor[0] = bigRect[i].x + (static_cast<float>((j - total_rect) % 2) * rect[j].size);
				rect[j].coor[1] = bigRect[i].y + (static_cast<float>((j - total_rect) / 2) * rect[j].size);
				for (int k = 0; k < 3; ++k) {
					rect[j].color[k] = bigRect[i].color[k];
				}
			}
			total_rect += 4;
			break;
		case 1:		// 대각선 네방향
			for (int j = total_rect; j < total_rect + 4; ++j) {
				rect[j].rect_num = i;
				switch (j - total_rect) {
				case 0:
					rect[j].move_way = 1;
					break;
				case 1:
					rect[j].move_way = 3;
					break;
				case 2:
					rect[j].move_way = 7;
					break;
				case 3:
					rect[j].move_way = 9;
					break;
				}
				rect[j].coor[0] = bigRect[i].x + (static_cast<float>((j - total_rect) % 2) * rect[j].size);
				rect[j].coor[1] = bigRect[i].y + (static_cast<float>((j - total_rect) / 2) * rect[j].size);
				for (int k = 0; k < 3; ++k) {
					rect[j].color[k] = bigRect[i].color[k];
				}
			}
			total_rect += 4;
			break;
		case 2:		// 8방향
			for (int j = total_rect; j < total_rect + 8; ++j) {
				rect[j].rect_num = i;
				switch (j - total_rect) {
				case 0:
					rect[j].move_way = 1;
					rect[j].coor[0] = bigRect[i].x + (0 * rect[j].size);
					rect[j].coor[1] = bigRect[i].y + (0 * rect[j].size);
					break;
				case 1:
					rect[j].move_way = 2;
					rect[j].coor[0] = bigRect[i].x + (0.5 * rect[j].size);
					rect[j].coor[1] = bigRect[i].y + (0 * rect[j].size);
					break;
				case 2:
					rect[j].move_way = 3;
					rect[j].coor[0] = bigRect[i].x + (1 * rect[j].size);
					rect[j].coor[1] = bigRect[i].y + (0 * rect[j].size);
					break;
				case 3:
					rect[j].move_way = 4;
					rect[j].coor[0] = bigRect[i].x + (0 * rect[j].size);
					rect[j].coor[1] = bigRect[i].y + (0.5 * rect[j].size);
					break;
				case 4:
					rect[j].move_way = 6;
					rect[j].coor[0] = bigRect[i].x + (1 * rect[j].size);
					rect[j].coor[1] = bigRect[i].y + (0.5 * rect[j].size);
					break;
				case 5:
					rect[j].move_way = 7;
					rect[j].coor[0] = bigRect[i].x + (0 * rect[j].size);
					rect[j].coor[1] = bigRect[i].y + (1 * rect[j].size);
					break;
				case 6:
					rect[j].move_way = 8;
					rect[j].coor[0] = bigRect[i].x + (0.5 * rect[j].size);
					rect[j].coor[1] = bigRect[i].y + (1 * rect[j].size);
					break;
				case 7:
					rect[j].move_way = 9;
					rect[j].coor[0] = bigRect[i].x + (1 * rect[j].size);
					rect[j].coor[1] = bigRect[i].y + (1 * rect[j].size);
					break;
				}
				for (int k = 0; k < 3; ++k) {
					rect[j].color[k] = bigRect[i].color[k];
				}
			}
			total_rect += 8;
			break;
		}
	}
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 6");					// 윈도우 생성(윈도우 이름)

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
	glutTimerFunc(100, TimerFunc, 1);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < total_rect; ++i) {
		glColor3f(rect[i].color[0], rect[i].color[1], rect[i].color[2]);
		glRectf(rect[i].coor[0], rect[i].coor[1],
			rect[i].coor[0] + rect[i].size, rect[i].coor[1] + rect[i].size);
	}
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);;
}

float x_conversion(int x)
{
	return (static_cast<float>(x) - (width / 2)) / (width / 2);
}

float y_conversion(int y)
{
	return ((static_cast<float>(y) * -1) + (height / 2)) / (height / 2);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < 5; ++i) {
			if ((bigRect[i].x <= x_conversion(x) && bigRect[i].x + bigRect[i].size >= x_conversion(x)) &&
				(bigRect[i].y <= y_conversion(y) && bigRect[i].y + bigRect[i].size >= y_conversion(y))) {
				for (int j = 0; j < total_rect; ++j) {
					if (rect[j].rect_num == i) {
						rect[j].flag = true;
					}
				}
			}
		}
	}
	glutPostRedisplay();
}

void TimerFunc(int value)
{
	for (int i = 0; i < total_rect; ++i) {
		if (rect[i].flag) {
			switch (rect[i].move_way) {
			case 1:
				rect[i].coor[0] -= 0.02;
				rect[i].coor[1] -= 0.02;
				if(rect[i].size >= 0)
					rect[i].size -= 0.01;
				break;
			case 2:
				rect[i].coor[1] -= 0.02;
				if (rect[i].size >= 0)
					rect[i].size -= 0.01;
				break;
			case 3:
				rect[i].coor[0] += 0.02;
				rect[i].coor[1] -= 0.02;
				if (rect[i].size >= 0)
					rect[i].size -= 0.01;
				break;
			case 4:
				rect[i].coor[0] -= 0.02;
				if (rect[i].size >= 0)
					rect[i].size -= 0.01;
				break;
			case 6:
				rect[i].coor[0] += 0.02;
				if (rect[i].size >= 0)
					rect[i].size -= 0.01;
				break;
			case 7:
				rect[i].coor[0] -= 0.02;
				rect[i].coor[1] += 0.02;
				if (rect[i].size >= 0)
					rect[i].size -= 0.01;
				break;
			case 8:
				rect[i].coor[1] += 0.02;
				if (rect[i].size >= 0)
					rect[i].size -= 0.01;
				break;
			case 9:
				rect[i].coor[0] += 0.02;
				rect[i].coor[1] += 0.02;
				if (rect[i].size >= 0)
					rect[i].size -= 0.01;
				break;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}