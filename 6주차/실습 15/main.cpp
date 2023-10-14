#include "Filetobuf.h"
#include "Line.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void SpecialKeyboard(int, int, int);
void TimerF_1(int);
void TimerF_2(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height, show_shape;
bool culling, rotate_x, rotate_y, xplus, yplus;
GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Line Line_x(0);
Line Line_y(1);

Mesh cube;
Mesh pyramid;

void main(int argc, char** argv)
{
	rotate_x = rotate_y = false;
	culling = true;
	show_shape = 0;
	width = height = 800;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 15");					// ������ ����(������ �̸�)

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	shaderProgramID = make_shaderProgram();			// ���̴� ���α׷� �����
	Line_x.Initialize(&shaderProgramID);
	Line_y.Initialize(&shaderProgramID);

	cube.Initialize(&shaderProgramID, "cube.obj");
	pyramid.Initialize(&shaderProgramID, "pyramid.obj");

	cube.Scale(0.07);
	pyramid.Scale(0.07);
	
	cube.Rotate(30, 1, 0, 0); cube.Rotate(-30, 0, 1, 0);
	pyramid.Rotate(30, 1, 0, 0); pyramid.Rotate(-30, 0, 1, 0);

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glUseProgram(shaderProgramID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (culling) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}

	Line_x.Draw();
	Line_y.Draw();

	switch (show_shape) {
	case 0:
		cube.Draw();
		break;
	case 1:
		pyramid.Draw();
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
	vertexSource = filetobuf("VertexShader.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	fragmentSource = filetobuf("FragmentShader.glsl");
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
	case 'c':
		show_shape = 0;
		break;
	case 'p':
		show_shape = 1;
		break;
	case 'h':
		if (culling)
			culling = false;
		else
			culling = true;
		break;
	case 'w':
		cube.TransView(false);
		pyramid.TransView(false);
		break;
	case 'W':
		cube.TransView(true);
		pyramid.TransView(true);
		break;
	case 'x':
		xplus = true;
		if (not rotate_x) {
			rotate_x = true;
			glutTimerFunc(100, TimerF_1, 0);
		}
		break;
	case 'X':
		xplus = false;
		if (not rotate_x) {
			rotate_x = true;
			glutTimerFunc(100, TimerF_1, 0);
		}
		break;
	case 'y':
		yplus = true;
		if (not rotate_y) {
			rotate_y = true;
			glutTimerFunc(100, TimerF_2, 1);
		}
		break;
	case 'Y':
		yplus = false;
		if (not rotate_y) {
			rotate_y = true;
			glutTimerFunc(100, TimerF_2, 1);
		}
		break;
	case 's':
		rotate_x = rotate_y = false;
		cube.trans_Initialize();
		pyramid.trans_Initialize();
		cube.Rotate(30, 1, 0, 0); cube.Rotate(-30, 0, 1, 0);
		pyramid.Rotate(30, 1, 0, 0); pyramid.Rotate(-30, 0, 1, 0);
		break;
	}
	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
		cube.Move(-0.05, 0, 0);
		pyramid.Move(-0.05, 0, 0);
	}
	else if (key == GLUT_KEY_UP) {
		cube.Move(0, 0.05, 0);
		pyramid.Move(0, 0.05, 0);
	}
	else if (key == GLUT_KEY_RIGHT) {
		cube.Move(0.05, 0, 0);
		pyramid.Move(0.05, 0, 0);
	}
	else if (key == GLUT_KEY_DOWN) {
		cube.Move(0, -0.05, 0);
		pyramid.Move(0, -0.05, 0);
	}
	glutPostRedisplay();
}

void TimerF_1(int value)
{
	if (xplus) {
		cube.Rotate(10, 1, 0, 0);
		pyramid.Rotate(10, 1, 0, 0);
	}
	else {
		cube.Rotate(-10, 1, 0, 0);
		pyramid.Rotate(-10, 1, 0, 0);
	}
	glutPostRedisplay();
	if (rotate_x)
		glutTimerFunc(100, TimerF_1, 0);
}

void TimerF_2(int value)
{
	if (yplus) {
		cube.Rotate(10, 0, 1, 0);
		pyramid.Rotate(10, 0, 1, 0);
	}
	else {
		cube.Rotate(-10, 0, 1, 0);
		pyramid.Rotate(-10, 0, 1, 0);
	}
	glutPostRedisplay();
	if (rotate_y)
		glutTimerFunc(100, TimerF_2, 1);
}