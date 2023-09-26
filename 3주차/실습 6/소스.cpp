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

struct Rect {			// ���� �簢��
	float color[3];		// ���� �簢�� ����
	float coor[2] = { 0, 0 };		// ���� �簢�� ��ǥ
	float size = 0.2;			// ���� �簢�� ũ��
	int move_way;		// ���� �������� ����(���е� ����)
	int rect_num;		// ���° rect�� ���ԵƳ�
	bool flag = false;	// Ŭ�� �Ƴ�?
};
Rect rect[40];

struct BIGRECT {
	float x;
	float y;
	float size = 0.4;
	int move_method;	// � ������� �����ų�
	float color[3];
};
BIGRECT bigRect[5];

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void TimerFunc(int);

float x_conversion(int);			// ������ x��ǥ�� gl��ǥ�� �ٲ��ִ� �Լ�
float y_conversion(int);			// ������ y��ǥ�� gl��ǥ�� �ٲ��ִ� �Լ�

int width, height;
int total_rect = 0;

void main(int argc, char** argv)
{
	width = height = 800;
	// ū �簢�� ���� �־��ֱ�
	for (int i = 0; i < 5; ++i) {
		bigRect[i].move_method = method(dre);
		bigRect[i].x = coor_urd(dre);
		bigRect[i].y = coor_urd(dre);
		for (int j = 0; j < 3; ++j) {
			bigRect[i].color[j] = color_urd(dre);
		}
		switch (bigRect[i].move_method) {
		case 0:		// �����¿� �׹���
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
		case 1:		// �밢�� �׹���
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
		case 2:		// 8����
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
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 6");					// ������ ����(������ �̸�)

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
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunc, 1);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < total_rect; ++i) {
		glColor3f(rect[i].color[0], rect[i].color[1], rect[i].color[2]);
		glRectf(rect[i].coor[0], rect[i].coor[1],
			rect[i].coor[0] + rect[i].size, rect[i].coor[1] + rect[i].size);
	}
	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)						// �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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