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

float x_conversion(int);			// ������ x��ǥ�� gl��ǥ�� �ٲ��ִ� �Լ�
float y_conversion(int);			// ������ y��ǥ�� gl��ǥ�� �ٲ��ִ� �Լ�

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
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 5");					// ������ ����(������ �̸�)

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
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
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
	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)						// �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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
	if (((erase.coor[0] - erase.size >= food.coor[0] - 0.02) &&	//���� ��
		(erase.coor[0] - erase.size <= food.coor[0] + 0.02) &&
		(erase.coor[1] + erase.size >= food.coor[1] - 0.02) &&
		(erase.coor[1] + erase.size <= food.coor[1] + 0.02)) ||
		((erase.coor[0] + erase.size >= food.coor[0] - 0.02) &&	// ������ ��
			(erase.coor[0] + erase.size <= food.coor[0] + 0.02) &&
			(erase.coor[1] + erase.size >= food.coor[1] - 0.02) &&
			(erase.coor[1] + erase.size <= food.coor[1] + 0.02)) ||
		((erase.coor[0] - erase.size >= food.coor[0] - 0.02) &&	// ���� �Ʒ�
			(erase.coor[0] - erase.size <= food.coor[0] + 0.02) &&
			(erase.coor[1] - erase.size >= food.coor[1] - 0.02) &&
			(erase.coor[1] - erase.size <= food.coor[1] + 0.02)) ||
		((erase.coor[0] + erase.size >= food.coor[0] - 0.02) &&	// ������ �Ʒ�
			(erase.coor[0] + erase.size <= food.coor[0] + 0.02) &&
			(erase.coor[1] - erase.size >= food.coor[1] - 0.02) &&
			(erase.coor[1] - erase.size <= food.coor[1] + 0.02)) ||
		((food.coor[0] - 0.02 >= erase.coor[0] - erase.size) && // ���� ��
			(food.coor[0] - 0.02 <= erase.coor[0] + erase.size) &&
			(food.coor[1] + 0.02 >= erase.coor[1] - erase.size) &&
			(food.coor[1] + 0.02 <= erase.coor[1] + erase.size)) ||
		((food.coor[0] + 0.02 >= erase.coor[0] - erase.size) && // ������ ��
			(food.coor[0] + 0.02 <= erase.coor[0] + erase.size) &&
			(food.coor[1] + 0.02 >= erase.coor[1] - erase.size) &&
			(food.coor[1] + 0.02 <= erase.coor[1] + erase.size)) ||
		((food.coor[0] - 0.02 >= erase.coor[0] - erase.size) && // ���� �Ʒ�
			(food.coor[0] - 0.02 <= erase.coor[0] + erase.size) &&
			(food.coor[1] - 0.02 >= erase.coor[1] - erase.size) &&
			(food.coor[1] - 0.02 <= erase.coor[1] + erase.size)) ||
		((food.coor[0] + 0.02 >= erase.coor[0] - erase.size) && // ���� ��
			(food.coor[0] + 0.02 <= erase.coor[0] + erase.size) &&
			(food.coor[1] - 0.02 >= erase.coor[1] - erase.size) &&
			(food.coor[1] - 0.02 <= erase.coor[1] + erase.size)))
		return true;
	else
		return false;
}