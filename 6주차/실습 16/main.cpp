#include "Filetobuf.h"
#include "Line.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void TimerF_1(int);
void TimerF_2(int);
void TimerF_3(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
bool t1, t2, t3, xplus, yplus, rplus;
bool left_move, right_move, change_mesh;
GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Line Line_x(0);
Line Line_y(1);
Line Line_z(2);

Mesh cone;
Mesh cube;
Mesh pyramid;
Mesh sphere;

void main(int argc, char** argv)
{
	left_move = right_move = true;
	t1 = t2 = t3 = xplus = yplus = rplus = change_mesh = false;
	width = height = 800;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 14");					// ������ ����(������ �̸�)

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
	Line_z.Initialize(&shaderProgramID);

	cone.Initialize(&shaderProgramID, "cone.obj");
	cube.Initialize(&shaderProgramID, "cube.obj");
	pyramid.Initialize(&shaderProgramID, "pyramid.obj");
	sphere.Initialize(&shaderProgramID, "sphere.obj");

	cone.Scale(0.02);
	cube.Scale(0.02);
	pyramid.Scale(0.02);
	sphere.Scale(0.02);

	cube.Rotate_world(-50, 0, 1, 0);
	cone.Rotate_world(-50, 0, 1, 0);
	pyramid.Rotate_world(-50, 0, 1, 0);
	sphere.Rotate_world(-50, 0, 1, 0);

	cube.Move(-0.5, 0, 0);
	cone.Move(0.5, 0, 0);
	pyramid.Move(-0.5, 0, 0);
	sphere.Move(0.5, 0, 0);


	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glUseProgram(shaderProgramID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	Line_x.Draw();
	Line_y.Draw();
	Line_z.Draw();

	if (change_mesh) {
		pyramid.Draw();
		sphere.Draw();
	}
	else {
		cone.Draw();
		cube.Draw();
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
	case 'x':
		xplus = true; 
		if (not t1) {
			t1 = true;
			glutTimerFunc(100, TimerF_1, 0);
		}
		break;
	case 'X':
		xplus = false;
		if (not t1) {
			t1 = true;
			glutTimerFunc(100, TimerF_1, 0);
		}
		break;
	case 'y':
		yplus = true;
		if (not t2) {
			t2 = true;
			glutTimerFunc(100, TimerF_2, 1);
		}
		break;
	case 'Y':
		yplus = false;
		if (not t2) {
			t2 = true;
			glutTimerFunc(100, TimerF_2, 1);
		}
		break;
	case '1':
		left_move = true;
		right_move = false;
		break;
	case '2':
		left_move = false;
		right_move = true;
		break;
	case '3':
		left_move = true;
		right_move = true;
		break;
	case 'r':
		rplus = true;
		if (not t3) {
			t3 = true;
			glutTimerFunc(100, TimerF_3, 2);
		}
		break;
	case 'R':
		rplus = false;
		if (not t3) {
			t3 = true;
			glutTimerFunc(100, TimerF_3, 2);
		}
		break;
	case 'c':
		if (change_mesh)
			change_mesh = false;
		else
			change_mesh = true;
		break;
	case 's':
		t1 = t2 = t3 = false;
		cube.T_format();
		cone.T_format();
		pyramid.T_format();
		sphere.T_format();
		break;
	}
	glutPostRedisplay();
}

void TimerF_1(int value) {
	if (xplus) {
		if (left_move) {
			cube.Rotate(10, 0, 1, 0);
			pyramid.Rotate(10, 0, 1, 0);
		}
		if (right_move) {
			cone.Rotate(10, 0, 1, 0);
			sphere.Rotate(10, 0, 1, 0);
		}
	}
	else {
		if (left_move) {
			cube.Rotate(-10, 0, 1, 0);
			pyramid.Rotate(-10, 0, 1, 0);
		}
		if (right_move) {
			cone.Rotate(-10, 0, 1, 0);
			sphere.Rotate(-10, 0, 1, 0);
		}
	}
	glutPostRedisplay();
	if (t1)
		glutTimerFunc(100, TimerF_1, 0);
}

void TimerF_2(int value)
{
	if (yplus) {
		if (left_move) {
			cube.Rotate(10, 1, 0, 0);
			pyramid.Rotate(10, 1, 0, 0);
		}
		if (right_move) {
			cone.Rotate(10, 1, 0, 0);
			sphere.Rotate(10, 1, 0, 0);
		}
	}
	else {
		if (left_move) {
			cube.Rotate(-10, 1, 0, 0);
			pyramid.Rotate(-10, 1, 0, 0);
		}
		if (right_move) {
			cone.Rotate(-10, 1, 0, 0);
			sphere.Rotate(-10, 1, 0, 0);
		}
	}
	glutPostRedisplay();
	if (t2)
		glutTimerFunc(100, TimerF_2, 1);
}

void TimerF_3(int value)
{
	if (rplus) {
		cube.Rotate_world(10, 0, 1, 0);
		cone.Rotate_world(10, 0, 1, 0);
		pyramid.Rotate_world(10, 0, 1, 0);
		sphere.Rotate_world(10, 0, 1, 0);
	}
	else {
		cube.Rotate_world(-10, 0, 1, 0);
		cone.Rotate_world(-10, 0, 1, 0);
		pyramid.Rotate_world(-10, 0, 1, 0);
		sphere.Rotate_world(-10, 0, 1, 0);
	}
	glutPostRedisplay();
	if (t3)
		glutTimerFunc(100, TimerF_3, 2);
}