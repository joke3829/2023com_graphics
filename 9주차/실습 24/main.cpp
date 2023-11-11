#include "Filetobuf.h"
#include "Floor.h"
#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void KeyboardUp(unsigned char, int, int);
void Special(int, int, int);
void SpecialUp(int, int, int);
void TimerF(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
bool move_w, move_a, move_s, move_d;
bool y_rot, Y_rot, z_move, Z_move;

bool falling;
int falling_count;

GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü


Camera camera;
Projection proj;

Robot robot;
Floor myfloor;

Wall wall[4];

void main(int argc, char** argv)
{
	width = height = 800;
	falling = true;
	move_w = move_a = move_s = move_d = false;
	y_rot = Y_rot = z_move = Z_move = false;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 24");					// ������ ����(������ �̸�)

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

	camera.Initialize(&shaderProgramID);
	proj.Initialize(&shaderProgramID);

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd(0.0, 0.9);
	std::uniform_int_distribution<int> uid(-8, 8);
	for (Wall& w : wall) {
		w.Initialize(&shaderProgramID, urd(dre), urd(dre), urd(dre), 0);
	}
	//wall[0].Rotate(90, glm::vec3(1, 0, 0));
	wall[0].Rotate(-90, glm::vec3(0, 1, 0)); wall[0].Move(glm::vec3(-10, 10, 0));
	wall[1].Rotate(180, glm::vec3(0, 1, 0)); wall[1].Move(glm::vec3(0, 10, -10));
	wall[2].Rotate(90, glm::vec3(0, 1, 0)); wall[2].Move(glm::vec3(10, 10, 0));
	wall[3].Rotate(-90, glm::vec3(1, 0, 0)); wall[3].Move(glm::vec3(0, 20, 0));

	robot.Initialize(&shaderProgramID);
	myfloor.Initialize(&shaderProgramID);

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(Special);
	glutSpecialUpFunc(SpecialUp);
	glutTimerFunc(50, TimerF, 0);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glUseProgram(shaderProgramID);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	for (Wall w : wall)
		w.Draw();

	myfloor.Draw();

	robot.Draw();

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
	case 'w':
		move_w = true;
		break;
	case 'a':
		move_a = true;
		break;
	case 's':
		move_s = true;
		break;
	case 'd':
		move_d = true;
		break;
	case 'z':
		z_move = true;
		break;
	case 'Z':
		Z_move = true;
		break;
	case 'y':
		y_rot = true;
		break;
	case 'Y':
		Y_rot = true;
		break;
	case 'x':
		camera.Move(4);
		break;
	case 'X':
		camera.Move(6);
		break;
	case '+':
		robot.speed_control('+');
		break;
	case '-':
		robot.speed_control('-');
		break;
	case 'g':
		if (falling) {
			falling = false;
			falling_count = 0;
		}
		break;
	case 'i':
		robot.Trans_init(glm::vec3(0, 0, 0));
		break;
	}
	glutPostRedisplay();
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		move_w = false;
		break;
	case 'a':
		move_a = false;
		break;
	case 's':
		move_s = false;
		break;
	case 'd':
		move_d = false;
		break;
	case 'z':
		z_move = false;
		break;
	case 'Z':
		Z_move = false;
		break;
	case 'y':
		y_rot = false;
		break;
	case 'Y':
		Y_rot = false;
		break;
	}
	glutPostRedisplay();
}

void TimerF(int value)
{
	// �÷��̾� 1 ����
	if (robot.state_check()) {
		if (move_w) {
			robot.Move(8);
			for (int i = 0; i < 3; ++i) {
				if (wall[i].crash_check(robot)) {
					robot.Move(2);
					robot.angle_change(wall[i].reflect_vector(robot));
					break;
				}
			}
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					if (robot.check_crash(myfloor.getMesh(i, j))) {
						robot.Move(2);
						break;
					}
				}
			}
		}
		if (move_a)
			robot.Rotate(4);
		if (move_s) {
			robot.Move(2);
			for (int i = 0; i < 3; ++i) {
				if (wall[i].crash_check(robot)) {
					robot.Move(8);
					break;
				}
			}
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					if (robot.check_crash(myfloor.getMesh(i, j))) {
						robot.Move(8);
						break;
					}
				}
			}
		}
		if (move_d)
			robot.Rotate(6);
		if (move_w || move_a || move_s || move_d)
			robot.arm_legAni();
		else
			robot.stand_ani();
		if (z_move)
			camera.dis_plus(8);
		if (Z_move)
			camera.dis_plus(2);
		if (y_rot)
			camera.rotate_pos(4);
		if (Y_rot)
			camera.rotate_pos(6);

		if (falling) {
			robot.fallen(2);
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					if (robot.check_crash(myfloor.getMesh(i, j))) {
						robot.fallen(5);
						break;
					}
				}
			}
		}
		else {
			if (falling_count >= 4) {
				robot.fallen(2);
				for (int i = 0; i < 10; ++i) {
					for (int j = 0; j < 10; ++j) {
						if (robot.check_crash(myfloor.getMesh(i, j))) {
							robot.fallen(5);
							falling = true;
							break;
						}
					}
				}
			}
			else {
				robot.fallen(8);
				falling_count += 1;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(50, TimerF, 0);
}


void Special(int key, int x, int y)
{
	glutPostRedisplay();
}

void SpecialUp(int key, int x, int y)
{
	glutPostRedisplay();
}