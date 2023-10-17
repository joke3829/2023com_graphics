#include "Filetobuf.h"
#include "spiral.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void Special(int, int, int);
void TimerF_1(int);
void TimerF_2(int);
void TimerF_3(int);
void TimerF_4(int);
void TimerF_5(int);
void TimerF_6(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height, t5_count, t6_count;
float sx_1, sx_2;
bool t1, t2, t3, t4, t5, t6, xplus, yplus, rplus, tr;
bool left_move, right_move, change_mesh;
bool move_plus;
int select_what;
GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Line Line_x(0);
Line Line_y(1);
Line Line_z(2);

Mesh cone;
Mesh cube;

spiral spi[2];

void main(int argc, char** argv)
{
	select_what = 0;
	left_move = right_move = true;
	t1 = t2 = t3 = t4 = t5 = t6 = xplus = yplus = rplus = change_mesh = tr = false;
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
	spi[0].Initialize(&shaderProgramID, 0);
	spi[1].Initialize(&shaderProgramID, 1);

	cube.scale_size = 0.01;
	cone.scale_size = 0.01;
	cube.scale_world_size = 1;
	cone.scale_world_size = 1;

	cone.Scale(cube.scale_size);
	cube.Scale(cone.scale_size);
	cube.Scale_world(cube.scale_world_size);
	cone.Scale_world(cone.scale_world_size);

	cube.Rotate_world(-50, 0, 1, 0);
	cone.Rotate_world(-50, 0, 1, 0);

	cube.move_dis_y = cube.move_dis_z = 0;
	cube.move_dis_x = -0.7000; cube.Move(cube.move_dis_x, 0, 0);
	cone.move_dis_y = cone.move_dis_z = 0;
	cone.move_dis_x = 0.7000; cone.Move(cone.move_dis_x, 0, 0);


	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
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

	cone.Draw();
	cube.Draw();

	spi[0].Draw();
	spi[1].Draw();

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
		if (not t4) {
			t4 = true;
			sx_1 = cube.move_dis_x;
			sx_2 = cone.move_dis_x;
			if (sx_1 < sx_2)
				move_plus = true;
			else
				move_plus = false;
			glutTimerFunc(100, TimerF_4, 3);
		}
		break;
	case '2':
		if (not t5) {
			t5 = true;
			t5_count = 0;
			glutTimerFunc(100, TimerF_5, 4);
		}
		break;
	case '3':
		if (not t6) {
			t6 = true;
			t6_count = 0;
			glutTimerFunc(100, TimerF_6, 5);
		}
		break;
	case 'r':
		if (not tr) {
			tr = true;
			cube.move_dis_x = cube.move_dis_y = cube.move_dis_z = 0;
			cone.move_dis_x = cone.move_dis_y = cone.move_dis_z = 0;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			cube.rotate_wolrd_rad = 0;
			cone.rotate_wolrd_rad = 0;
			glutTimerFunc(170, TimerF_3, 2);
		}
		break;
	/*case 'c':
		if (change_mesh)
			change_mesh = false;
		else
			change_mesh = true;
		break;*/
	case 's':	// ��ġ �ʱ�ȭ
		t1 = t2 = t3 = false;
		cube.T_format();
		cone.T_format();

		cube.M_format();
		cube.move_dis_x = -0.7; 
		cube.move_dis_y = cube.move_dis_z = 0;
		cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
		cube.scale_size = 0.01; cube.scale_world_size = 1;
		cube.Scale(cube.scale_size); cube.Scale_world(cube.scale_world_size);

		cone.M_format();
		cone.move_dis_x = 0.7;
		cone.move_dis_y = cone.move_dis_z = 0;
		cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
		cone.scale_size = 0.01; cone.scale_world_size = 1;
		cone.Scale(cone.scale_size); cone.Scale_world(cone.scale_world_size);
		break;
	case 't':
		break;
	case '+':	// �ڱ� �ڽ� ����
		cube.scale_size += 0.001;
		cone.scale_size += 0.001;
		cube.Scale(cube.scale_size);
		cone.Scale(cone.scale_size);
		break;
	case '-':	// �ڱ� �ڽ� ����
		cube.scale_size -= 0.001;
		cone.scale_size -= 0.001;
		cube.Scale(cube.scale_size);
		cone.Scale(cone.scale_size);
		break;
	case 'p':	// ������ ���� Ȯ��
		cube.scale_world_size += 0.05;
		cone.scale_world_size += 0.05;
		cube.Scale_world(cube.scale_world_size);
		cone.Scale_world(cone.scale_world_size);
		break;
	case 'm':	// ������ ���� ���
		cube.scale_world_size -= 0.05;
		cone.scale_world_size -= 0.05;
		cube.Scale_world(cube.scale_world_size);
		cone.Scale_world(cone.scale_world_size);
		break;
	case 'c':
		select_what = 0;
		break;
	case 'v':
		select_what = 1;
		break;
	case 'b':
		select_what = 2;
		break;
	case 'i':		// z�� �̵�
		switch (select_what) {
		case 0:
			cube.move_dis_z += 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			break;
		case 1:
			cone.move_dis_z += 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		case 2:
			cube.move_dis_z += 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			cone.move_dis_z += 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		}
		break;
	case 'k':		// z�� �̵�
		switch (select_what) {
		case 0:
			cube.move_dis_z -= 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			break;
		case 1:
			cone.move_dis_z -= 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		case 2:
			cube.move_dis_z -= 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			cone.move_dis_z  -= 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		}
		break;
	}
	glutPostRedisplay();
}

void TimerF_1(int value) {
	if (xplus) {
		if (left_move) {
			cube.Rotate(10, 0, 1, 0);
		}
		if (right_move) {
			cone.Rotate(10, 0, 1, 0);
		}
	}
	else {
		if (left_move) {
			cube.Rotate(-10, 0, 1, 0);
		}
		if (right_move) {
			cone.Rotate(-10, 0, 1, 0);
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
		}
		if (right_move) {
			cone.Rotate(10, 1, 0, 0);
		}
	}
	else {
		if (left_move) {
			cube.Rotate(-10, 1, 0, 0);
		}
		if (right_move) {
			cone.Rotate(-10, 1, 0, 0);
		}
	}
	glutPostRedisplay();
	if (t2)
		glutTimerFunc(100, TimerF_2, 1);
}

void TimerF_3(int value)
{
	cube.move_dis_x -= 0.0005;
	cone.move_dis_x += 0.0005;
	cube.rotate_wolrd_rad += 0.01;
	cone.rotate_wolrd_rad += 0.01;
	cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
	cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
	cube.Rotate_world(cube.rotate_wolrd_rad, 0, 1, 0);
	cone.Rotate_world(cone.rotate_wolrd_rad, 0, 1, 0);
	glutPostRedisplay();
	if (tr)
		glutTimerFunc(50, TimerF_3, 2);
}

void TimerF_4(int value)
{
	cube.M_format();
	cone.M_format();
	if (move_plus) {
		cube.move_dis_x += 0.05;
		cone.move_dis_x -= 0.05;
		if (sx_2 <= cube.move_dis_x)
			t4 = false;
	}
	else {
		cube.move_dis_x -= 0.05;
		cone.move_dis_x += 0.05;
		if (sx_2 >= cube.move_dis_x)
			t4 = false;
	}
	cube.Move(cube.move_dis_x, 0, 0);
	cone.Move(cone.move_dis_x, 0, 0);
	glutPostRedisplay();
	if (t4)
		glutTimerFunc(100, TimerF_4, 3);
}

void TimerF_5(int value)
{
	cube.Rotate_world(10, 0, 1, 0);
	cone.Rotate_world(10, 0, 1, 0);
	t5_count++;
	if (t5_count == 18)
		t5 = false;
	glutPostRedisplay();
	if(t5)
		glutTimerFunc(100, TimerF_5, 4);
}

void TimerF_6(int value)
{
	cube.Rotate_world(10, 0, 0, 1);
	cone.Rotate_world(10, 0, 0, 1);
	t6_count++;
	if (t6_count == 18)
		t6 = false;
	glutPostRedisplay();
	if (t6)
		glutTimerFunc(100, TimerF_6, 5);
}

void Special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		switch (select_what) {
		case 0:
			cube.move_dis_x += 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			break;
		case 1:
			cone.move_dis_x += 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		case 2:
			cube.move_dis_x += 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			cone.move_dis_x += 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		}
		break;
	case GLUT_KEY_RIGHT:
		switch (select_what) {
		case 0:
			cube.move_dis_x -= 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			break;
		case 1:
			cone.move_dis_x -= 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		case 2:
			cube.move_dis_x -= 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			cone.move_dis_x -= 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		}
		break;
	case GLUT_KEY_UP:
		switch (select_what) {
		case 0:
			cube.move_dis_y += 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			break;
		case 1:
			cone.move_dis_y += 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		case 2:
			cube.move_dis_y += 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			cone.move_dis_y += 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		}
		break;
	case GLUT_KEY_DOWN:
		switch (select_what) {
		case 0:
			cube.move_dis_y -= 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			break;
		case 1:
			cone.move_dis_y -= 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		case 2:
			cube.move_dis_y -= 0.01;
			cube.Move(cube.move_dis_x, cube.move_dis_y, cube.move_dis_z);
			cone.move_dis_y -= 0.01;
			cone.Move(cone.move_dis_x, cone.move_dis_y, cone.move_dis_z);
			break;
		}
		break;
	}
	glutPostRedisplay();
}