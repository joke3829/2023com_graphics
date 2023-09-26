#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<random>

struct Food {
	float coor[2];
	float color[3];
};
Food food[40];

struct ERASE {
	float coor[2];
	float color[3];
	float size = 0.04;
};
ERASE erase;

std::random_device rd;
std::mt19937 dre(rd());
std::uniform_real_distribution<float> urd(-1.0, 1.0);
std::uniform_real_distribution<float> urd_c(0.0, 1.0);
std::uniform_int_distribution uid(20, 40);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void Motion(int, int);
bool intersect(Food, ERASE);

float x_conversion(int);			// 윈도우 x좌표를 gl죄표로 바꿔주는 함수
float y_conversion(int);			// 윈도우 y좌표를 gl좌표로 바꿔주는 함수

int width, height;
int food_num;
bool left;

void main(int argc, char** argv)
{
	left = false;
	food_num = uid(dre);
	width = height = 800;
	for (int i = 0; i < food_num; ++i) {
		food[i].coor[0] = urd(dre);
		food[i].coor[1] = urd(dre);
		for (int j = 0; j < 3; ++j)
			food[i].color[j] = urd_c(dre);
	}
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 5");					// 윈도우 생성(윈도우 이름)

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < food_num; ++i) {
		glColor3f(food[i].color[0], food[i].color[1], food[i].color[2]);
		glRectf(food[i].coor[0] - 0.02, food[i].coor[1] - 0.02,
			food[i].coor[0] + 0.02, food[i].coor[1] + 0.02);
	}
	if (left) {
		glColor3f(erase.color[0], erase.color[1], erase.color[2]);
		glRectf(erase.coor[0] - erase.size, erase.coor[1] - erase.size,
			erase.coor[0] + erase.size, erase.coor[1] + erase.size);
	}
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);;
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
		food_num = uid(dre);
		for (int i = 0; i < food_num; ++i) {
			food[i].coor[0] = urd(dre);
			food[i].coor[1] = urd(dre);
			for (int j = 0; j < 3; ++j)
				food[i].color[j] = urd_c(dre);
		}
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	float coor_x = x_conversion(x);
	float coor_y = y_conversion(y);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		left = true;
		erase.coor[0] = coor_x;
		erase.coor[1] = coor_y;
		erase.size = 0.03;
		for (int i = 0; i < 3; ++i) {
			erase.color[i] = 0;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		left = false;
	}
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	if (left) {
		erase.coor[0] = x_conversion(x);
		erase.coor[1] = y_conversion(y);
		for (int i = 0; i < food_num; ++i) {
			if (intersect(food[i], erase)) {
				food_num--;
				erase.size += 0.005;
				for (int j = 0; j < 3; ++j) {
					erase.color[j] = (erase.color[j] + food[i].color[j]) / 2;
				}
				for (int j = i; j < food_num; ++j) {
					food[j] = food[j + 1];
				}
			}
		}
		glutPostRedisplay();
	}
}

float x_conversion(int x)
{
	return (static_cast<float>(x) - (width / 2)) / (width / 2);
}

float y_conversion(int y)
{
	return ((static_cast<float>(y) * -1) + (height / 2)) / (height / 2);
}

bool intersect(Food food, ERASE erase)
{
	if (((erase.coor[0] - erase.size >= food.coor[0] - 0.02) &&	//왼쪽 위
		(erase.coor[0] - erase.size <= food.coor[0] + 0.02) &&
		(erase.coor[1] + erase.size >= food.coor[1] - 0.02) &&
		(erase.coor[1] + erase.size <= food.coor[1] + 0.02)) ||
		((erase.coor[0] + erase.size >= food.coor[0] - 0.02) &&	// 오른쪽 위
			(erase.coor[0] + erase.size <= food.coor[0] + 0.02) &&
			(erase.coor[1] + erase.size >= food.coor[1] - 0.02) &&
			(erase.coor[1] + erase.size <= food.coor[1] + 0.02)) ||
		((erase.coor[0] - erase.size >= food.coor[0] - 0.02) &&	// 왼쪽 아래
			(erase.coor[0] - erase.size <= food.coor[0] + 0.02) &&
			(erase.coor[1] - erase.size >= food.coor[1] - 0.02) &&
			(erase.coor[1] - erase.size <= food.coor[1] + 0.02)) ||
		((erase.coor[0] + erase.size >= food.coor[0] - 0.02) &&	// 오른쪽 아래
			(erase.coor[0] + erase.size <= food.coor[0] + 0.02) &&
			(erase.coor[1] - erase.size >= food.coor[1] - 0.02) &&
			(erase.coor[1] - erase.size <= food.coor[1] + 0.02)) ||
		((food.coor[0] - 0.02 >= erase.coor[0] - erase.size) && // 왼쪽 위
			(food.coor[0] - 0.02 <= erase.coor[0] + erase.size) &&
			(food.coor[1] + 0.02 >= erase.coor[1] - erase.size) &&
			(food.coor[1] + 0.02 <= erase.coor[1] + erase.size)) ||
		((food.coor[0] + 0.02 >= erase.coor[0] - erase.size) && // 오른쪽 위
			(food.coor[0] + 0.02 <= erase.coor[0] + erase.size) &&
			(food.coor[1] + 0.02 >= erase.coor[1] - erase.size) &&
			(food.coor[1] + 0.02 <= erase.coor[1] + erase.size)) ||
		((food.coor[0] - 0.02 >= erase.coor[0] - erase.size) && // 왼쪽 아래
			(food.coor[0] - 0.02 <= erase.coor[0] + erase.size) &&
			(food.coor[1] - 0.02 >= erase.coor[1] - erase.size) &&
			(food.coor[1] - 0.02 <= erase.coor[1] + erase.size)) ||
		((food.coor[0] + 0.02 >= erase.coor[0] - erase.size) && // 왼쪽 위
			(food.coor[0] + 0.02 <= erase.coor[0] + erase.size) &&
			(food.coor[1] - 0.02 >= erase.coor[1] - erase.size) &&
			(food.coor[1] - 0.02 <= erase.coor[1] + erase.size)))
		return true;
	else
		return false;
}